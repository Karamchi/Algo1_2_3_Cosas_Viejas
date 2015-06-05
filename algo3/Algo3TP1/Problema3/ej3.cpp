#include "ej3.hpp"
// #include <chrono>

using namespace std;

int main(){

    //Aca se parsean los datos de entrada

    int lado;
    std::cin >> lado;
    int c_iniciales;
    std::cin >> c_iniciales;
    
    int medida = (lado*lado);
    
    int medida = (lado*lado);

    //Estas dos funciones crean el Tablero y el Tablero Final
    //que van  a ser utilizados por la funcion auxiliar

    t_final* tablero_final = (t_final*) malloc(medida*2);
    tablero_t* tablero = crear_tablero(lado);

    //La funcion Recorrer pone todas las fichas iniciales en el tablero, luego
    //crea una Lista Enlazada y le agrega un nodo por cada casilla libre
    //del tablero. Devuelve un puntero a la lista.

    //Si el tablero ya esta lleno devuelve un puntero null, la funcion main
    //lo intercepta abajo y devuelve la solucion. Si al tablero tiene 1 solo
    //lugar libre, devuelve una ficha puesta ahi

    lista_t* camino = recorrer(tablero, c_iniciales, tablero_final);
    
    if(camino == (lista_t*)0){

        cout << tablero->libres << endl;

        if(tablero->libres ==1){
            int k=0;
            int j=1;
            int i=1;
            while(i<=lado){
                while(j<=lado){
                    if((tablero->lugar[k].amenazas == 0) and (!(tablero_final[k].inicial))){
                        cout << i  << ' ' << j << endl;
                    }
                    k++;
                    j++;
                    
                }
                j=1;
                i++;
            }
        }

        free(tablero->lugar);
        free(tablero);
        free(tablero_final);
        
    }else{

        //Si entramos aca es porque el tablero necesita computarse

        int solucion;

        //Abajo se decide un valor maximo de fichas necesarias
        //para completar el tablero
        
        int max_potencial = (lado*(((lado+4)/5)))+c_iniciales;
        int maximo = medida;
        if(lado>4){
            if(max_potencial<maximo){
                maximo = max_potencial;
            }
        }

        //Se llama a la funcion Auxiliar para computar la solucion
        //Esta devuelve la cantidad total de caballos que tiene el
        //tablero al estar completo. Empieza a recorrer desde el 
        //primer nodo de la lista

        solucion = auxiliar(tablero, camino->primero, &maximo, tablero_final);

        //A la solucion hay que restarle la cantidad de fichas iniciales

        solucion = solucion - c_iniciales;

        //Se imprime la solucion en pantalla

        cout << solucion << endl;
        int k=0;
        int j=1;
        int i=1;
        while(i<=lado){
            while(j<=lado){
                if((tablero_final[k].ocupada) and (!(tablero_final[k].inicial))){
                    cout << i  << ' ' << j << endl;
                }
                k++;
                j++;
                
            }
            j=1;
            i++;
        }

        //Se libera la memoria y la funcion termina :)

        free(tablero->lugar);
        free(tablero);
        free(tablero_final);
        lista_borrar(camino);
    }
}


lista_t* recorrer(tablero_t* tablero, int c_iniciales, t_final* tablero_final){
    int size = tablero->lado;

    int size = tablero->lado;

    //Este ciclo parsea los caballos de entrada y los pone en el tablero

    while(c_iniciales>0){
        int fila;
        std::cin >> fila;
        fila = fila - 1;
        int columna;
        std::cin >> columna;
        columna = columna-1;
        agregar_ficha(tablero, columna, fila);
        tablero_final[columna+fila*size].inicial = true;
        c_iniciales--;
    }

    //Si el tablero puede resolverse sin computar, se devuelve un puntero null

    if(tablero->libres <= 1){
        return (lista_t*)0;
    }

    //Se cra una lista enlazada

    lista_t* lista = lista_crear();

    //Por cada casillero libre, se agrega un nodo a la lista

    nodo_t* nodo;
    int i = 0;
    int x = 0;
    int y = 0;

    while(y<size){
        while(x<size){
            if(!(tablero->lugar[i].ocupada)){
                lista_agregar(lista, x, y);
                tablero_final[x+y*size].inicial = false;
            }
            x++;
            i++;
        }
    y++;  
    x=0;
    }
    
return lista;

}

//Esta funcion agrega una ficha al tablero

void agregar_ficha(tablero_t* tablero, int x, int y){

    int lado = tablero->lado;
    int pos = x+lado*y;

    //Aca se actualizan los atributos relacionados al lugar
    //en donde se pone el caballo

    tablero->lugar[pos].ocupada = true;
    tablero->ocupadas++;
    if (tablero->lugar[pos].amenazas == 0){
        tablero->libres--;
    }

    //Aca se actualizan los lugares que amenaza la nueva ficha

    if(x-1>=0){
        if(y-2>=0){
            tablero->lugar[pos-1-lado*2].amenazas++;
            if((tablero->lugar[pos-1-lado*2].amenazas == 1) and !(tablero->lugar[pos-1-lado*2].ocupada)){
                tablero->libres--;}}
        if(y+2<lado){
            tablero->lugar[pos-1+lado*2].amenazas++;
            if((tablero->lugar[pos-1+lado*2].amenazas == 1) and !(tablero->lugar[pos-1+lado*2].ocupada)){
                tablero->libres--;}}
    }
    if(x-2>=0){
        if(y-1>=0){
            tablero->lugar[pos-2-lado].amenazas++;
            if((tablero->lugar[pos-2-lado].amenazas == 1) and !(tablero->lugar[pos-2-lado].ocupada)){
                tablero->libres--;}}
        if(y+1<lado){
            tablero->lugar[pos-2+lado].amenazas++;
            if((tablero->lugar[pos-2+lado].amenazas == 1) and !(tablero->lugar[pos-2+lado].ocupada)){
                tablero->libres--;}}
    }
    if(x+1<lado){
        if(y-2>=0){
            tablero->lugar[pos+1-lado*2].amenazas++;
            if((tablero->lugar[pos+1-lado*2].amenazas == 1) and !(tablero->lugar[pos+1-lado*2].ocupada)){
                tablero->libres--;}}
        if(y+2<lado){
            tablero->lugar[pos+1+lado*2].amenazas++;
            if((tablero->lugar[pos+1+lado*2].amenazas == 1) and !(tablero->lugar[pos+1+lado*2].ocupada)){
                tablero->libres--;}}
    }
    if(x+2<lado){
        if(y-1>=0){
            tablero->lugar[pos+2-lado].amenazas++;
            if((tablero->lugar[pos+2-lado].amenazas == 1) and !(tablero->lugar[pos+2-lado].ocupada)){
                tablero->libres--;}}    
        if(y+1<lado){
            tablero->lugar[pos+2+lado].amenazas++;
            if((tablero->lugar[pos+2+lado].amenazas == 1) and !(tablero->lugar[pos+2+lado].ocupada)){
                tablero->libres--;}}            
    }

    return;
}

    //Esta funcion elimina una ficha al tablero

void eliminar_ficha(tablero_t* tablero, int x, int y){

    int lado = tablero->lado;
    int pos = x+lado*y;

    //Aca se actualizan los atributos relacionados al lugar
    //en donde estaba el caballo

    tablero->lugar[pos].ocupada = false;
    tablero->ocupadas--;
    if (tablero->lugar[pos].amenazas == 0){
        tablero->libres++;
    }

    //Aca se actualizan los lugares que amenazaba la ficha a sacar

    if(x-1>=0){
        if(y-2>=0){
            tablero->lugar[pos-1-lado*2].amenazas--;
            if((tablero->lugar[pos-1-lado*2].amenazas == 0) and !(tablero->lugar[pos-1-lado*2].ocupada)){
                tablero->libres++;}}
        if(y+2<lado){
            tablero->lugar[pos-1+lado*2].amenazas--;
            if((tablero->lugar[pos-1+lado*2].amenazas == 0) and !(tablero->lugar[pos-1+lado*2].ocupada)){
                tablero->libres++;}}
    }
    if(x-2>=0){
        if(y-1>=0){
            tablero->lugar[pos-2-lado].amenazas--;
            if((tablero->lugar[pos-2-lado].amenazas == 0) and !(tablero->lugar[pos-2-lado].ocupada)){
                tablero->libres++;}}
        if(y+1<lado){
            tablero->lugar[pos-2+lado].amenazas--;
            if((tablero->lugar[pos-2+lado].amenazas == 0) and !(tablero->lugar[pos-2+lado].ocupada)){
                tablero->libres++;}}
    }
    if(x+1<lado){
        if(y-2>=0){
            tablero->lugar[pos+1-lado*2].amenazas--;
            if((tablero->lugar[pos+1-lado*2].amenazas == 0) and !(tablero->lugar[pos+1-lado*2].ocupada)){
                tablero->libres++;}}
        if(y+2<lado){
            tablero->lugar[pos+1+lado*2].amenazas--;
            if((tablero->lugar[pos+1+lado*2].amenazas == 0) and !(tablero->lugar[pos+1+lado*2].ocupada)){
                tablero->libres++;}}
    }
    if(x+2<lado){
        if(y-1>=0){
            tablero->lugar[pos+2-lado].amenazas--;
            if((tablero->lugar[pos+2-lado].amenazas == 0) and !(tablero->lugar[pos+2-lado].ocupada)){
                tablero->libres++;}}
        
        if(y+1<lado){
            tablero->lugar[pos+2+lado].amenazas--;
            if((tablero->lugar[pos+2+lado].amenazas == 0) and !(tablero->lugar[pos+2+lado].ocupada)){
                tablero->libres++;}}
    }

    return;
}

//Esta funcion crea un Tablero y lo inicializa vacio

tablero_t* crear_tablero(int lado){

    int medida = lado*lado;
    tablero_t* nuevo_tablero = (tablero_t*)malloc(11);
    nuevo_tablero->lugar = (casilla_t*) malloc(medida*2);
    nuevo_tablero->lado = lado;
    nuevo_tablero->libres = medida;
    nuevo_tablero->ocupadas = 0;
    while(medida>0){
        nuevo_tablero->lugar[medida-1].ocupada = false;
        nuevo_tablero->lugar[medida-1].amenazas = 0;
        medida--;
    }

    return nuevo_tablero;
}

//Esta funcion crea una lista vacia

lista_t* lista_crear(){

    lista_t* lista = (lista_t*) malloc(16);
    lista->primero = (nodo_t*)0;
    lista->ultimo = (nodo_t*)0;

    return lista;
}

//Esta funcion borra una lista y todos los nodos contenidos en ella

void lista_borrar(lista_t* lista){

    nodo_t* nodo = lista->primero;
    nodo_t* prox;

    while(nodo!= (nodo_t*) 0){
        prox = nodo->proximo;
        free(nodo);
        nodo = prox;
    }

    free(lista);

    return;
}

//Esta funcion agrega un nodo a la lista con los atributos pasados por parametro

nodo_t* lista_agregar(lista_t* lista, int x, int y){

    nodo_t* nodo = (nodo_t*) malloc(10);
    nodo->x = x;
    nodo->y = y;
    
    if(lista->primero == (nodo_t*)0){
        lista->primero = nodo;
    }else{
        lista->ultimo->proximo = nodo;
    }

    nodo->proximo = (nodo_t*)0;
    lista->ultimo = nodo;

    return nodo;
}

//Esta funcion computa la cantidad

int auxiliar(tablero_t* tablero, nodo_t* actual, int* max, t_final* tablero_final){

    //Primero se inicializan algunas variables para darle mas claridad al codigo

    int lado = tablero->lado;

    //Las soluciones se inicializan en un valor alto
    //por si no se puede seguir avanzado en el tablero

    int solucion1 = lado*lado;
    int solucion2 = solucion1;

    int x = actual->x;
    int y = actual->y;
    int pos = x+lado*y;

    bool alcanza = true;

    //Abajo se chequea si se puede avanzar sin poner un caballo en el casillero actual

    if((x>0) and (y>1)){
        alcanza = ((tablero->lugar[pos-1-2*lado].amenazas>0)or(tablero->lugar[pos-1-2*lado].ocupada));
        if(alcanza){
            if(x+2 == lado){
                alcanza = ((tablero->lugar[pos+1-2*lado].amenazas>0)or(tablero->lugar[pos+1-2*lado].ocupada));
            }else if(y+1==lado){
                alcanza = (tablero->lugar[pos].amenazas > 0);
                if((alcanza) and (x>1)){
                    alcanza = ((tablero->lugar[pos-2-lado].amenazas>0)or(tablero->lugar[pos-2-lado].ocupada));
                }
            }
        }
    }
    
    //Si lo de arriba dio True y no estamos en el final de la lista, avanzamos 1 casillero

    if((alcanza) and (actual->proximo != (nodo_t*)0)){
        solucion1 = auxiliar(tablero, actual->proximo, max, tablero_final);
    }

    //Despues de obtener una solucion dejando el casillero vacio o de
    //decidir que no se puede avanzar, se pone un caballo en la casilla actual

    agregar_ficha(tablero, x, y);

    
    
    
    if(tablero->libres <= 1){

        //Si el tablero queda con 0 o 1 lugares libres, encontramos una solucion

        solucion2 = tablero->ocupadas+tablero->libres;
        if(solucion2<*max){

            //Si la solucion es mejor a la optima encontrada se actualiza la optima
            //Y se actualiza el tablero final
            
            *max = solucion2;
            int i = 0;
            while(i<(lado*lado)){
                tablero_final[i].ocupada = ((tablero->lugar[i].ocupada) or (tablero->lugar[i].amenazas == 0));
                i++;
            }
        }
    }else{

        //Si todavia no llegamos a un tablero completo,
        //nos fijamos si podemos seguir poniendo caballos y
        //si no llegamos al final de la lista

        if(((*max)-(tablero->ocupadas)) > (((tablero->libres)+8)/9)){
            if((actual->proximo != (nodo_t*)0)){

                //Si se pasan ambas verificaciones avanzamos en el tablero tirando recursion

                solucion2 = auxiliar(tablero, actual->proximo, max, tablero_final);
            }
        }
    }

    //Sacamos el caballo que pusimos y el tablero queda
    //como cuando empezo la funcion

    eliminar_ficha(tablero, x, y);

    //Devolvemos la solucion mas chica de las encontradas por recursion

    if(solucion2<solucion1){
        return solucion2;
    }
    
    return solucion1;
}

//Esta funcion imprime en pantalla el estado del tablero,
//Fue usada para Debuggear

void imprimir_estado(tablero_t* tablero){
    printf("%i libres, %i ocupadas \n", tablero->libres, tablero->ocupadas);
    for (int i = 0; i < (tablero->lado)*(tablero->lado); ++i){
        printf("Ficha %i, %i, %i amenazas \n", i, (int)tablero->lugar[i].ocupada, tablero->lugar[i].amenazas);
        }
    return;
}
