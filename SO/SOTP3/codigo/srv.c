#include "srv.h"

/*
 *  Ejemplo de servidor que tiene el "sí fácil" para con su
 *  cliente y no se lleva bien con los demás servidores.
 *
 */

//Entre Cliente y Servidor se comunican bien a travez del MPI, no hay que modificarlo

void servidor(int mi_cliente) 
{
    MPI_Status status; int origen, tag;
    int hay_pedido_local = FALSE;
    int listo_para_salir = FALSE;
    
	//Variables del algoritmo del paper
    int me = mi_nro; //El número entre los servidores solos.
    int n = cant_ranks/2; //El número de servidores.
    int our_sequence_number;
	int highest_sequence_number = 0;
    int outstanding_reply_count;
	int requesting_critical_section = FALSE;
	int reply_deferred[cant_ranks/2];
	int i;
	for (i=0; i<cant_ranks/2; ++i){
		reply_deferred[i] = FALSE;
	}
	int terminaron = 0; //Los servidores que terminaron hasta el momento. Esto es para que se cierren una vez que terminaron todos.
	
	//Semaforos no ultilizamos ya que el servidor trabaja como un solo proceso a diferencia del Paper que tiene muchos procesos que se encargan de los distintos mensajes.
	
    int msj[1]; //Buffer para el mensaje de REQUEST
	

    //Las variables globales que dice el paper son dentro de cada servidor. Es que el paper considera subprocesos por cada nodo.
    
    while( ! listo_para_salir ) {
        
        MPI_Recv(msj, 1, MPI_INT, ANY_SOURCE, ANY_TAG, COMM_WORLD, &status);//PUEDE ACEPTAR TODOS LOS TAG.
        origen = status.MPI_SOURCE; 			//número de rank del source en el COMM_WORLD
        tag = status.MPI_TAG;
        
        if (tag == TAG_PEDIDO) {			//Puedo recibir muchos TAG_PEDIDOS
            assert(origen == mi_cliente);
            debug("Mi cliente solicita acceso exclusivo");
            assert(hay_pedido_local == FALSE);
            hay_pedido_local = TRUE;
   			requesting_critical_section = TRUE;
   			our_sequence_number = highest_sequence_number+1;
   			outstanding_reply_count = n-1;
        	msj[0] = our_sequence_number;
        	for (i=0; i<n; ++i){
        		if (i!=me){
        			MPI_Send(msj, 1, MPI_INT, i*2, TAG_REQUEST, COMM_WORLD); //MANDÉ EL MSJ. VER EL TIPO DE SEND.
        		}
        	}
        	if(n == 1){
        		debug("Dándole permiso (NO frutesco)");
            	MPI_Send(NULL, 0, MPI_INT, mi_cliente, TAG_OTORGADO, COMM_WORLD); //Cuando es un Único servidor
        	}
        }
        
        else if (tag == TAG_LIBERO) {			//Release the Critical Section.
            assert(origen == mi_cliente);
            requesting_critical_section = FALSE;
            for (i=0; i<n; ++i){
            	if(reply_deferred[i]){
            		reply_deferred[i] = FALSE;
            		MPI_Send(NULL, 0, MPI_INT, i*2, TAG_REPLY, COMM_WORLD);
            	}
            }
            debug("Mi cliente libera su acceso exclusivo");
            assert(hay_pedido_local == TRUE);
            hay_pedido_local = FALSE;
        }
        
        else if (tag == TAG_REPLY) {
        	debug("Recibo Reply!");
        	outstanding_reply_count = outstanding_reply_count-1;
        	if(outstanding_reply_count == 0){
        		debug("Dándole permiso (NO frutesco)");
            	MPI_Send(NULL, 0, MPI_INT, mi_cliente, TAG_OTORGADO, COMM_WORLD); //Cuando se cumple esto, garantizo al exclusión entonces le mando el TAG_OTORGADO.
        	}
        }
        
        else if (tag == TAG_REQUEST) {			//k y j del paper son msj[0] y origen/2 respectivamente.
        	debug("Recibo Request!");
        	if(msj[0] >= highest_sequence_number){
        		highest_sequence_number = msj[0];
        	}
        	int defer_it = requesting_critical_section && ((msj[0] > our_sequence_number) || (msj[0] == our_sequence_number && origen/2 > me));
							//Es TRUE si tenemos prioridad sobre el servidor origen/2.

        	if(defer_it){
        		reply_deferred[origen/2] = TRUE;
        	} else {
        		MPI_Send(NULL, 0, MPI_INT, origen, TAG_REPLY, COMM_WORLD);
        	}
        }
        
        else if (tag == TAG_TERMINE) {
            assert(origen == mi_cliente);
            debug("Mi cliente avisa que terminó");
            terminaron = terminaron+1; 			//Se suma este servidor.
            if(terminaron == n){			//Cerramos cuando todos terminan
            	listo_para_salir = TRUE;
            }
	    for (i=0; i<n; ++i){			//Mando que terminé
	   	if (i!=me){
			MPI_Send(NULL, 0, MPI_INT, i*2, TAG_TERMINE_SERV, COMM_WORLD);
		}
	    }
        }
        
        else if (tag == TAG_TERMINE_SERV) {
            debug("Un servidor terminó");
            terminaron = terminaron+1;
            if(terminaron == n){			//Cerramos cuando todos terminan
            	listo_para_salir = TRUE;
            }
        }
    }
}

