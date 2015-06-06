
#include <iostream>
#include <string>
#include <locale>
#include <stdlib.h>
#include "interfaz.h"
#include "test.h"

//Pause no compila en linux

using namespace std;

bool peliculaCreada = false;
bool ticketCreado = false;
bool cineCreado = false;

Genero leerGenero(string genero)
{
    //TODO toupper?
    if (genero == "Aventura" || genero == "A")
        return Aventura;

    if (genero == "Comedia" || genero == "C")
        return Comedia;
    
    if (genero == "Drama" || genero == "D")
        return Drama;

    if (genero == "Romantica" || genero == "R")
        return Romantica;

    if (genero == "Terror" || genero == "T")
        return Terror;
    
    return Aventura;
}

bool leerBool(string val) {
    if (val == "t" || val == "s" || val == "true" || val == "si")
        return true;

    return false;
}


void MostrarOpciones(string* tipos, int tam)
{
    cout << endl;
    for (int i = 0; i < tam; i++) cout << i << " - " << tipos[i] << endl;
}

void MenuPrincipal()
{
    cout.setf(ios::boolalpha);

    bool exit = false;
    int maximaOpcion = 3;

    while (!exit)
    {
        cout << endl
                << "Cines!!" << endl
                << "0. Pelicula" << endl
                << "1. Ticket" << endl
                << "2. Cine" << endl
                << "3. Test" << endl;

        int opt = LeerOpcion(maximaOpcion);
        switch(opt)
        {
            case 0:
            {
                LimpiarPantalla();
                MenuPelicula();
                break;
            }
            case 1:
            {
                LimpiarPantalla();
                MenuTicket();
                break;
            }
            case 2:
            {
                LimpiarPantalla();
                MenuCine();
                break;
            }
            case 3:
            {
                LimpiarPantalla();
                correrTests();
                break;
            }
        }

    }
}

/////// MENU Pelicula

Pelicula pelicula;
void MenuPelicula()
{
    int maximaOpcion = 2;

    cout << "Creando Pelicula" << endl
            << "0. Volver al Menu Principal" << endl
            << "1. Crear pelicula" << endl
            << "2. Cargar pelicula" << endl;
    if (peliculaCreada)
    {
        maximaOpcion = 8;
        cout << "3. Guardar pelicula" << endl
            << "4. Mostrar" << endl
            << "5. Nombre" << endl
            << "6. Generos" << endl
            << "7. Actores" << endl
            << "8. es3D" << endl;
    }

    int opt = LeerOpcion(maximaOpcion);

    LimpiarPantalla();
    switch(opt)
    {
        case 0:
        {
            LimpiarPantalla();
            break;
        }
        case 1:
        {
            LimpiarPantalla();
            pelicula = MenuCrearPelicula();
            peliculaCreada = true;
            LimpiarPantalla();
            MenuPelicula();
            break;
        }
        case 2:
        {
            LimpiarPantalla();
            ifstream archivoEntrada;
            AbrirArchivoParaLeer(archivoEntrada);
            pelicula.cargar(archivoEntrada);
            archivoEntrada.close();
            peliculaCreada = true;
            LimpiarPantalla();
            MenuPelicula();
            break;
        }
        case 3:
        {
            LimpiarPantalla();
            ofstream archivoSalida;

            AbrirArchivoParaEscribir(archivoSalida);
            pelicula.guardar(archivoSalida);
            archivoSalida.close();

            LimpiarPantalla();
            MenuPelicula();
            break;
        }
        case 4:
        {
            LimpiarPantalla();
            pelicula.mostrar(cout);
            Pausar();
            LimpiarPantalla();
            MenuPelicula();
            break;
        }
        case 5:
        {
            cout << "Nombre: " << pelicula.nombreP() << endl;
            Pausar();
            LimpiarPantalla();
            MenuPelicula();
            break;
        }
        case 6:
        {
            cout << "Generos: " << pelicula.generosP() << endl;
            Pausar();
            LimpiarPantalla();
            MenuPelicula();
            break;
        }
        case 7:
        {
            cout << "Actores: " << pelicula.actoresP() << endl;
            Pausar();
            LimpiarPantalla();
            MenuPelicula();
            break;
        }
        case 8:
        {
            cout << "3D: " << pelicula.es3DP() << endl;
            Pausar();
            LimpiarPantalla();
            MenuPelicula();
            break;
        }
    }
}

Lista<Genero> leerGeneros(){
    Lista<Genero> generos;
    string strGenero;
    string ingresarMas = "s";
    while(ingresarMas == "s") {
        cout << "Ingrese un genero (Aventura (A), Comedia (C), Drama (D), Romantica (R), Terror (T))" << endl;
        cin >> strGenero;
        generos.agregarAtras(leerGenero(strGenero));
        cout << "Desea ingresar otro genero?[s/n]" << endl;
        cin >> ingresarMas;
    }
    
    return generos;
}


Lista<Actor> leerActores(){
    Lista<Actor> actores;
    string actor;
    string ingresarMas = "s";
    while(ingresarMas == "s") {
        cout << "Ingrese un actor" << endl;
        
        cin.get(); //descartar \n que quedó buffereado
        
        getline(cin, actor);
        actores.agregarAtras(actor);
        cout << "Desea ingresar otro actor?[s/n]" << endl;
        cin >> ingresarMas;
    }
    
    return actores;
}

Pelicula MenuCrearPelicula()
{
    string nombre;
    Lista<Genero> generos;
    Lista<Actor> actores;
    string str3d;

    cout << "Ingrese el nombre de la pelicula: " << endl;
    
    
    cin.get(); //descartar \n que quedó buffereado
    
    getline(cin, nombre);
    generos = leerGeneros();    
    actores = leerActores();    
    cout << "Es 3d? [s/n]: " << endl;
    cin >> str3d;

    return Pelicula(nombre, generos, actores, leerBool(str3d));
}

/////// MENU TICKET

Ticket ticket;

void MenuTicket()
{
    int maximaOpcion = 2;

    cout << "Creando ticket" << endl
            << "0. Volver al Menu Principal" << endl
            << "1. Crear ticket" << endl
            << "2. Cargar ticket" << endl;
    if (ticketCreado)
    {
        maximaOpcion = 8;
        cout << "3. Usar" << endl
            << "4. Guardar" << endl
            << "5. Mostrar" << endl
            << "6. Pelicula" << endl
            << "7. Sala" << endl
            << "8. Usado" << endl;
    }

    int opt = LeerOpcion(maximaOpcion);

    LimpiarPantalla();
    switch(opt)
    {
        case 0:
        {
            LimpiarPantalla();
            break;
        }
        case 1:
        {
            LimpiarPantalla();
            ticket = MenuCrearTicket();
            ticketCreado = true;
            
            Pausar();
            LimpiarPantalla();
            MenuTicket();
            break;
        }
        case 2:
        {
            LimpiarPantalla();
            ifstream archivoEntrada;
            AbrirArchivoParaLeer(archivoEntrada);
            ticket.cargar(archivoEntrada);
            archivoEntrada.close();
            ticketCreado = true;
            LimpiarPantalla();
            MenuTicket();
            break;
        }
        case 3:
        {
            LimpiarPantalla();
            cout << "Usando ticket!" << endl;
            ticket.usarT();
            Pausar();
            LimpiarPantalla();
            MenuTicket();
            break;
        }
        case 4:
        {
            LimpiarPantalla();
            ofstream archivoSalida;

            AbrirArchivoParaEscribir(archivoSalida);
            ticket.guardar(archivoSalida);
            archivoSalida.close();

            LimpiarPantalla();
            MenuTicket();
            break;
        }
        case 5:
        {
            LimpiarPantalla();
            ticket.mostrar(cout);
            Pausar();
            LimpiarPantalla();
            MenuTicket();
            break;
        }
        case 6:
        {
            cout << "La pelicula es: ";
            ticket.peliculaT().mostrar(cout);
            cout << endl;
            Pausar();
            LimpiarPantalla();
            MenuTicket();
            break;
        }
        case 7:
        {
            cout << "La sala es: " << ticket.salaT() << endl;
            Pausar();
            LimpiarPantalla();
            MenuTicket();
            break;
        }
        case 8:
        {
            cout << "Usado?: " << ticket.usadoT() << endl;
            Pausar();
            LimpiarPantalla();
            MenuTicket();
            break;
        }
    }
}

Ticket MenuCrearTicket()
{
    Pelicula pelicula;
    Sala sala;
    string usado;

    cout << "Indique la pelicula: "<< endl;
    cout << "¿Cargar pelicula desde archivo? [s/n]: ";
    string desde_archivo;
    cin >> desde_archivo;
    if(desde_archivo == "s"){
		ifstream archivoEntrada;
		AbrirArchivoParaLeer(archivoEntrada);
		pelicula.cargar(archivoEntrada);
		archivoEntrada.close();
	}else {
		pelicula = MenuCrearPelicula();
	}
    cout << "Sala: " << endl;
    cin >> sala;
    cout << "Usado [s/n]: " << endl;
    cin >> usado;

    return Ticket(pelicula, sala, leerBool(usado));
}

/////// MENU CINE

Cine cine;

void MenuCine()
{
    int maximaOpcion = 2;

	cout << "Creando Cine" << endl
            << "0. Volver al Menu Principal" << endl
            << "1. Crear Cine" << endl
            << "-- Entrada/Salida --" << endl
            << "	2. Cargar Cine" << endl;
    if (cineCreado)
    {
        maximaOpcion = 17;
        cout << "	3. Guardar" << endl
            << "	4. Mostrar" << endl;
        cout << "-- Observadores --" << endl
			<< "	5. Nombre" << endl
			<< "	6. Peliculas" << endl
			<< "	7. Salas" << endl
			<< "	8. Sala de pelicula" << endl
			<< "	9. Espectadores" << endl
			<< "	10. Tickets vendidos sin usar" << endl
			<< "-- Operaciones --" << endl
			<< "	11. Abrir sala" << endl
            << "	12. Agregar pelicula" << endl
            << "	13. Cerrar sala" << endl
            << "	14. Pelicula de sala" << endl
            << "	15. Vender ticket" << endl
            << "	16. Ingresar a sala" << endl
            << "	17. Pasar a 3D" << endl;
            
            
            
            
            
            
            
            
            
            
    }

    int opt = LeerOpcion(maximaOpcion);

    LimpiarPantalla();
    switch(opt)
    {
        case 0:
        {
            LimpiarPantalla();
            break;
        }
        case 1:
        {
            LimpiarPantalla();
            cine = MenuCrearCine();
            cineCreado = true;
            LimpiarPantalla();
            MenuCine();
            break;
        }
        case 2:
        {
            LimpiarPantalla();
            ifstream archivoEntrada;
            AbrirArchivoParaLeer(archivoEntrada);
            cine.cargar(archivoEntrada);
            archivoEntrada.close();
            cineCreado = true;
            LimpiarPantalla();
            MenuCine();
            break;
        }

        case 3:
        {
            LimpiarPantalla();
            ofstream archivoSalida;

            AbrirArchivoParaEscribir(archivoSalida);
            cine.guardar(archivoSalida);
            archivoSalida.close();

            LimpiarPantalla();
            MenuCine();
            break;
        }
        case 4:
        {
            LimpiarPantalla();
            cine.mostrar(cout);
            Pausar();
            LimpiarPantalla();
            MenuCine();
            break;
        }
        case 5:
        {
            cout << "El nombre del cine es: " << cine.nombreC() << endl;

            Pausar();
            LimpiarPantalla();
            MenuCine();
            break;
        }
        case 6:
        {
            Lista<Pelicula> pelis = cine.peliculasC();
            cout << "Las peliculas del cine son: " << endl;
            for (int i = 0; i < pelis.longitud(); i++) {
                pelis.iesimo(i).mostrar(cout);
                cout << endl;
			}
            Pausar();
            LimpiarPantalla();
            MenuCine();
            break;
        }
        case 7:
        {
            cout << "Las salas del cine son: " << cine.salasC() << endl;

            Pausar();
            LimpiarPantalla();
            MenuCine();
            break;
        }
        case 8:
        {
            Nombre p;
            cout << "Ingrese el nombre de la pelicula" << endl;
            cin.get();
            getline(cin, p);
            cout << "Las sala de la pelicula es: " << cine.salaC(p) << endl;

            Pausar();
            LimpiarPantalla();
            MenuCine();
            break;
        }
        case 9:
        {
            Sala s;
            cout << "Ingrese la sala a consultar: " << endl;
            cin >> s;
            cout << "Los espectadores del cine son: " << cine.espectadoresC(s) << endl;

            Pausar();
            LimpiarPantalla();
            MenuCine();
            break;
        }
        case 10:
        {
            Lista<Ticket> tickets = cine.ticketsVendidosSinUsarC();
            cout << "Tickets vendidos sin usar: " << endl;
            for (int i = 0; i < tickets.longitud(); i++){
                tickets.iesimo(i).mostrar(cout);
                cout << endl;
            }
            Pausar();
            LimpiarPantalla();
            MenuCine();
            break;
        }
        case 11:
        {
            Sala s;
            cout << "Sala a abrir" << endl;
            cin >> s;

            cine.abrirSalaC(s);
            LimpiarPantalla();
            MenuCine();
            break;
        }
        case 12:
        {
            
            Sala s;
            cout << "Pelicula a crear" << endl;
            
            
			Pelicula p;

			cout << "Indique la pelicula: "<< endl;
			cout << "¿Cargar pelicula desde archivo? [s/n]: ";
			string desde_archivo;
			cin >> desde_archivo;
			if(desde_archivo == "s"){
				ifstream archivoEntrada;
				AbrirArchivoParaLeer(archivoEntrada);
				p.cargar(archivoEntrada);
				archivoEntrada.close();
				cout << "...cargado." << endl;
			}else {
				p = MenuCrearPelicula();
			}

            cout << "Sala a usar:" << endl;
            cin >> s;
            
            cine.agregarPeliculaC(p, s);
            LimpiarPantalla();
            MenuCine();
            break;
        }
        case 13:
        {
            Sala s;
            cout << "Sala a cerrar" << endl;
            cin >> s;
            
            cine.cerrarSalaC(s);
            LimpiarPantalla();
            MenuCine();
            break;
        }


        case 14:
        {
            Sala s;
            cout << "Ingrese la sala: " << endl;
            cin >> s;
            cout << "Pelicula: ";
            cine.peliculaC(s).mostrar(cout);

            Pausar();
            LimpiarPantalla();
            MenuCine();
            break;
        }
        case 15:
        {
            Nombre p;
            cout << "Ingrese la pelicula: " << endl;
            cin.get();
            getline(cin, p);
            Ticket t2 = cine.venderTicketC(p);
            
            cout << "Ticket: " << endl;
            t2.mostrar(cout);
            cout << "Cine: " << endl;
            cine.mostrar(cout);

            Pausar();
            LimpiarPantalla();
            MenuCine();
            break;
        }
        case 16:
        {
            int n;
        
            cout << "Tickets vendidos sin usar: " << endl;
            
            Lista<Ticket> tickets_vendidos = cine.ticketsVendidosSinUsarC();
			for (int i = 0; i < tickets_vendidos.longitud(); ++i) {
					cout << i << ". ";
					tickets_vendidos.iesimo(i).mostrar(cout);
					cout << endl;
			}
			cout << "Elija el ticket: ";
            cin >> n;
            Ticket t = tickets_vendidos.iesimo(n);            
            Ticket t2 = cine.ingresarASalaC(t.salaT(), t);
            cout << "Ticket: " << endl;
            t2.mostrar(cout);
            cout << "Cine: " << endl;
            cine.mostrar(cout);
            
            Pausar();
            LimpiarPantalla();
            MenuCine();
            break;
        }
        case 17:
        {
            Nombre p;
            cout << "Ingrese la pelicula: " << endl;
            cin.get();
            getline(cin, p);


            Pelicula p2 = cine.pasarA3DUnaPeliculaC(p);
            cout << "Pelicula: " << endl;
            p2.mostrar(cout);
            cout << endl;
            cout << "Cine: " << endl;
            cine.mostrar(cout);

            Pausar();
            LimpiarPantalla();
            MenuCine();
            break;
        }
    }
}

Cine MenuCrearCine()
{
    string nombre;
    cout << "Indicar nombre del cine: ";
    cin.get();
    getline(cin, nombre);

    return Cine(nombre);
}


//AUX
int LeerOpcion(int maxOpcion)
{
    cout << "  Ingrese una opcion [" << 0 << "-" << maxOpcion << "]: ";
    int opt;
    bool ok = false;
    while (!ok)
    {
        cin >> opt;
        ok = (opt <= maxOpcion);

        if (!ok)
            cout << "  Opcion incorrecta. Ingrese un numero entre [" << 1 << "-" << maxOpcion << "]: ";
    }
    return opt;
}

void Salir()
{
    cout << "Gracias, Vuelvan prontos!" << endl;
}

void Pausar()
{
    cout << endl;
    string opt = "n";
#ifdef WIN32
    system("Pause");
#else
    cout << "Presione Enter para continuar... ";
    getline(cin, opt);
    getline(cin, opt);

#endif

}

void LimpiarPantalla()
{
#ifdef WIN32
    system("cls");
#else
	system("clear");
#endif
}

void AbrirArchivoParaLeer(ifstream &archivo)
{
    cout << "  Ingrese nombre de archivo existente: ";
    string opt;
    bool ok = false;
    getline(cin, opt);
    getline(cin, opt);
    archivo.open(opt.c_str());
    ok = archivo.good();

    while (!ok)
    {
        cout << "  Valor incorrecto. Ingrese nombre de archivo existente: ";
        getline(cin, opt);
        archivo.open(opt.c_str());
        ok = archivo.good();
    }
}


void AbrirArchivoParaEscribir(ofstream &archivo)
{
    cout << "  Ingrese nombre de archivo: ";
    string opt;
    bool ok = false;
    getline(cin, opt);
    getline(cin, opt);
    archivo.open(opt.c_str());
    ok = archivo.good();

    while (!ok)
    {
        cout << "  Valor incorrecto. Ingrese nombre de archivo: ";
        getline(cin, opt);
        archivo.open(opt.c_str());
        ok = archivo.good();
    }
}
 

