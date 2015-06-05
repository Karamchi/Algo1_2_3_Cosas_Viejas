#include "DiccT.h"
#include "DiccOrd2.h"
#include "Titulo.h"

using namespace std;
using namespace aed2;

typedef Nat Cliente;
typedef Nat Acciones;

struct Wolfie {
    public:
        class itTitulo;
        Wolfie();
		~Wolfie();
        Conj<Cliente>::const_Iterador Clientes() const;
        Wolfie::itTitulo Titulos() const;
        Conj<Promesa>::const_Iterador promesasDe(const Cliente c) ;
        Nat accionesPorCliente(const Cliente c, const Nombre nt) const;
        Wolfie inaugurarWolfie (Conj<Cliente> cs);
        void agregarTitulo(const Titulo t);
        void actualizarCotizacion(const Nombre nt, Nat cot);
        void agregarPromesa(const Cliente c, Promesa p);
        bool enAlza(Nombre nt) ;

        //Esto está para facilitar el driver:
        //(Si no son const el driver explota)
        Nat cantClientes() const;
        Nat cantTitulos() const;

        itTitulo CrearIt() const;

        class itTitulo
        {
          public:

            itTitulo();

            itTitulo(const typename Wolfie::itTitulo& otro);

            itTitulo& operator = (const typename Wolfie::itTitulo& otro);

            bool HaySiguiente() const;
            Titulo Siguiente() const;
            void Avanzar();

          private:

            Conj<string>::const_Iterador itClaves;
            const Wolfie* wolfinator;
            itTitulo(const Wolfie* d);
            friend typename Wolfie::itTitulo Wolfie::CrearIt() const;
        };

private:
        struct datosCliente{
            Acciones _acc;
            Conj<Promesa> _pCompra;
            Conj<Promesa> _pVenta;
        };

        struct tupla1{
            Titulo _titulo;
            Acciones _cantWolfie;
            DiccAcot<Cliente, datosCliente> _diccCli;
        };
        struct tupla2{
            Cliente _cliente;
            Conj<Promesa> _promesas;
        };

        Conj<Cliente> _clientes;
        Conj<string> _titulos;
        DiccT<tupla1> _datosTitulo;
        DiccAcot<Cliente, Acciones> _accTxCliente;
        Conj<tupla2> _promUlt;

        DiccAcot<Cliente,datosCliente> crearDiccAccC (DiccAcot<Cliente, Acciones> cs, datosCliente t);
        Wolfie(const Conj<Cliente>);
};
