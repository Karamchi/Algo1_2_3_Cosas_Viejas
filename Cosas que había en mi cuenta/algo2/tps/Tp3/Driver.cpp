#include "Driver.h"


Driver::Driver(const Conj<Cliente>& clientes)
{
    w = w.inaugurarWolfie(clientes);
}

Driver::~Driver()
{
	//TODO
}

void Driver::AgregarTitulo(const NombreTitulo& nombre, Dinero cotizacion, Nat max_acciones)
{
    Titulo t;
    t = t.nuevoT(nombre, cotizacion, max_acciones);
    w.agregarTitulo(t);
}

void Driver::ActualizarCotizacion(const NombreTitulo& nombre, Nat cotizacion)
{
    w.actualizarCotizacion(nombre, cotizacion);
}

void Driver::AgregarPromesaDeCompra(const Cliente& cliente, const NombreTitulo& titulo, Dinero limite, Nat cantidad)
{
    Promesa p = Promesa();
    p = p.crearPromesa(titulo, comprar, limite, cantidad);
	w.agregarPromesa(cliente, p);
}

void Driver::AgregarPromesaDeVenta(const Cliente& cliente, const NombreTitulo& titulo, Dinero limite, Nat cantidad)
{
    Promesa p = Promesa();
    p = p.crearPromesa(titulo, vender, limite, cantidad);
	w.agregarPromesa(cliente, p);
}

Nat Driver::CantidadDeClientes() const
{
	return w.cantClientes();

}

//PRE: i < cardinal(clientes)
Cliente Driver::IesimoCliente(Nat i) const
{
    Conj<Cliente>::const_Iterador it = Conj<Cliente>::const_Iterador(w.Clientes());
    for (Nat j=0;j<i;j++){
        it.Avanzar();
    }
    return it.Siguiente();
}

Nat Driver::CantidadDeTitulos() const
{
    return w.cantTitulos();
}

NombreTitulo Driver::IesimoTitulo(Nat i) const {
    Wolfie::itTitulo it = w.Titulos();
    for (Nat j=0;j<i;j++){
        it.Avanzar();
    }
    return it.Siguiente().nombre();
}

//PRE: El título está
Nat Driver::MaxAccionesDe(const NombreTitulo& nombre_titulo) const
{
    Wolfie::itTitulo it = w.Titulos();
    while(it.Siguiente().nombre() != nombre_titulo){
        it.Avanzar();
    }
    return it.Siguiente().cantmax();
}

Dinero Driver::CotizacionDe(const NombreTitulo& nombre_titulo) const
{
    Wolfie::itTitulo it = w.Titulos();
    while(it.Siguiente().nombre() != nombre_titulo){
        it.Avanzar();
    }
    return it.Siguiente().cot();
}

bool Driver::EnAlza(const NombreTitulo& nombre_titulo) const
{
    Wolfie::itTitulo it = w.Titulos();
    while(it.Siguiente().nombre() != nombre_titulo){
        it.Avanzar();
    }
    return it.Siguiente().enalza();
}

Nat Driver::AccionesTotalesDe(const Cliente& cliente) const
{
    //voy iterando los títulos y le voy sumando a 'total' las acciones que tiene de it.Siguiente()
    Wolfie::itTitulo it = w.Titulos();
    Nat total = 0;
    while(it.HaySiguiente()){
        total+= w.accionesPorCliente(cliente, it.Siguiente().nombre());
        it.Avanzar();
    }
    return total;
}

Nat Driver::AccionesPorCliente(const Cliente& cliente, const NombreTitulo& nombre_titulo) const
{
    return w.accionesPorCliente(cliente, nombre_titulo);
}

//PRE: existe el titulo
Nat Driver::AccionesDisponibles(const NombreTitulo& nombre_titulo) const
{
    //Le asigno a total la cantidad max que tiene el titulo
    Wolfie::itTitulo it = w.Titulos();
    while(it.Siguiente().nombre() != nombre_titulo){
        it.Avanzar();
    }
    Nat total = it.Siguiente().cantmax();


    //voy iterando los clientes y les resto a total la cantidad de acciones que tenga de ese titulo
    Conj<Cliente>::const_Iterador it2 = Conj<Cliente>::const_Iterador(w.Clientes());
    while(it2.HaySiguiente()){
        total-= w.accionesPorCliente(it2.Siguiente(), nombre_titulo);
        it2.Avanzar();
    }
    return total;
}

bool Driver::PrometeComprar(const Cliente& cliente, const NombreTitulo& titulo) /** const */{
    Conj<Promesa>::const_Iterador it = w.promesasDe(cliente);
    while (it.HaySiguiente()){
        if (it.Siguiente().titulo() == titulo && it.Siguiente().tipo() == comprar){
            return true;
        } it.Avanzar();
    }
    return false;
}

Nat Driver::CantidadAComprar(const Cliente& cliente, const NombreTitulo& titulo) /** const */
{
	Conj<Promesa>::const_Iterador it = w.promesasDe(cliente);
    while (it.HaySiguiente()){
        if (it.Siguiente().titulo() == titulo && it.Siguiente().tipo() == comprar){
            return it.Siguiente().cantidad();
        } it.Avanzar();
    }
    return 0;
}

Dinero Driver::ValorEsperadoParaComprar(const Cliente& cliente, const NombreTitulo& titulo) /** const */
{
	Conj<Promesa>::const_Iterador it = w.promesasDe(cliente);
    while (it.HaySiguiente()){
        if (it.Siguiente().titulo() == titulo && it.Siguiente().tipo() == comprar){
            return it.Siguiente().limite();
        } it.Avanzar();
    }
    return 0;
}

bool Driver::PrometeVender(const Cliente& cliente, const NombreTitulo& titulo) /** const */
{
	Conj<Promesa>::const_Iterador it = w.promesasDe(cliente);
    while (it.HaySiguiente()){
        if (it.Siguiente().titulo() == titulo && it.Siguiente().tipo() == vender){
            return true;
        } it.Avanzar();
    }
    return false;
}


Nat Driver::CantidadAVender(const Cliente& cliente, const NombreTitulo& titulo) /** const */
{
	Conj<Promesa>::const_Iterador it = w.promesasDe(cliente);
    while (it.HaySiguiente()){
        if (it.Siguiente().titulo() == titulo && it.Siguiente().tipo() == vender){
            return it.Siguiente().cantidad();
        } it.Avanzar();
    }
    return 0;
}

Dinero Driver::ValorEsperadoParaVender(const Cliente& cliente, const NombreTitulo& titulo) /** const */
{
	Conj<Promesa>::const_Iterador it = w.promesasDe(cliente);
    while (it.HaySiguiente()){
        if (it.Siguiente().titulo() == titulo && it.Siguiente().tipo() == vender){
            return it.Siguiente().limite();
        } it.Avanzar();
    }
    return 0;
}
