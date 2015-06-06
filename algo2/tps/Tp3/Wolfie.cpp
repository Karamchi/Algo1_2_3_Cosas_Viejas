#include "Wolfie.h"


Wolfie::Wolfie(){
    _clientes=Conj<Cliente>();
    _accTxCliente=DiccAcot<Cliente,Acciones>();
    _datosTitulo=DiccT<tupla1>();
    _titulos=Conj<string>();
    _promUlt=Conj<tupla2>();
}

Wolfie::Wolfie(const Conj<Cliente> cl){
    _accTxCliente=DiccAcot<Cliente,Acciones>(cl.Cardinal());
    Conj<Cliente>::const_Iterador cs = cl.CrearIt();
    while (cs.HaySiguiente()) {
        _clientes.AgregarRapido(cs.Siguiente());
        _accTxCliente.Definir(cs.Siguiente(),0);
        cs.Avanzar();
    }   _datosTitulo=DiccT<tupla1>();
    _titulos=Conj<string>();
    _promUlt=Conj<tupla2>();
}

Wolfie::~Wolfie(){

	DiccT<tupla1>::Iterador it = _datosTitulo.CrearIt();

	while(it.HaySiguiente()){
		tupla1* punteroABorrar = &(_datosTitulo.Significado(it.SiguienteClave()));
		it.Avanzar();
		delete punteroABorrar;
	}
}


Conj<Cliente>::const_Iterador Wolfie::Clientes() const {
    return (_clientes.CrearIt());
}

Wolfie::itTitulo Wolfie::Titulos() const {
	return CrearIt();
}

Conj<Promesa>::const_Iterador Wolfie::promesasDe(const Cliente c){
    Conj<Promesa> prom;
    if (_promUlt.EsVacio() || (_promUlt.CrearIt().Siguiente()._cliente != c )) {

        Conj<Nombre>::Iterador t = _titulos.CrearIt();
        while (t.HaySiguiente()) {
            datosCliente datosCli = _datosTitulo.Significado(t.Siguiente())._diccCli.Significado(c);
            if (!datosCli._pCompra.EsVacio()) {
                prom.AgregarRapido((datosCli._pCompra.CrearIt()).Siguiente()) ;
            }
            if (!datosCli._pVenta.EsVacio()) {
                prom.AgregarRapido((datosCli._pVenta.CrearIt()).Siguiente()) ;
            }
            t.Avanzar();
        }
		tupla2 NuevaTdeUlt;
		NuevaTdeUlt._cliente = c;
		NuevaTdeUlt._promesas = prom;
		_promUlt = Conj<tupla2>();
		_promUlt.AgregarRapido(NuevaTdeUlt);
		return _promUlt.CrearIt().Siguiente()._promesas.CrearIt();

    } else {
		return _promUlt.CrearIt().Siguiente()._promesas.CrearIt();
    }
}

Nat Wolfie::accionesPorCliente(const Cliente c, const Nombre nt) const {
    return _datosTitulo.const_Significado(nt)._diccCli.const_Significado(c)._acc;
}
Wolfie Wolfie::inaugurarWolfie (Conj<Cliente> cl) {
    return Wolfie(cl);
}
void Wolfie::agregarTitulo(const Titulo t) {
    _titulos.AgregarRapido(t.nombre());
    datosCliente a;
    a._acc=0;
    a._pCompra=Conj<Promesa>();
    a._pVenta=Conj<Promesa>();
    tupla1* b = new tupla1();
    b->_titulo=t;
    b->_cantWolfie=0;
    b->_diccCli=DiccAcot<Cliente,datosCliente>(_clientes.Cardinal());
    DiccAcot<Cliente,Acciones>::Iterador cs=_accTxCliente.CrearIt();
    while (cs.HaySiguiente()) {
        (b->_diccCli).DefinirRapido(cs.Siguiente().clave, a);
        cs.Avanzar();
    }
    _datosTitulo.Definir(t.nombre(), *b);
}

struct tuplaCA{
    Cliente cliente;
    Acciones acciones;
};
///a chequear mergesort !
void Merge(Arreglo<tuplaCA> *a, Arreglo<tuplaCA> *b, Nat low, Nat pivot, Nat high) {
    Nat h;Nat i;Nat j;Nat k;
    h=low;
    i=low;
    j=pivot+1;
    while ((h<=pivot)&&(j<=high)) {
        if (((*a)[h]).cliente<=((*a)[j]).cliente) {
            b->Definir(i,(*a)[h]);
            h++;
        } else {
            b->Definir(i,(*a)[j]);
            j++;
        } i++;
    } if (h>pivot) {
        for (k=j; k<=high; k++) {
            b->Definir(i,(*a)[k]);
            i++;
        }
    } else {
        for (k=h; k<=pivot; k++) {
            b->Definir(i,(*a)[k]);
            i++;
        }
    } for(k=low; k<=high; k++) {
        (*a)[k]=(*b)[k];
    }
}

void MergesortAux(Arreglo<tuplaCA>* a,Arreglo<tuplaCA>* b, Nat low, Nat high) {
    Nat pivot;
    if(low<high) {
        pivot=(low+high)/2;
        MergesortAux(a,b,low,pivot);
        MergesortAux(a,b,pivot+1,high);
        Merge(a,b,low,pivot,high);
    }
}

void mergesort(Arreglo<tuplaCA> a){
    Arreglo<tuplaCA> b(a.Tamanho());
    MergesortAux(&a,&b,0,a.Tamanho()-1);
}

Arreglo<tuplaCA> DiccAcot2ArrOrd (DiccAcot<Cliente,Acciones> d) {
    DiccAcot<Cliente,Acciones>::Iterador di =d.CrearIt();
    Arreglo<tuplaCA> arr=Arreglo<tuplaCA>(d.CantClaves());
    for (Nat i=0;i<d.CantClaves();i++) {
        tuplaCA ca;
        ca.cliente=di.SiguienteClave();
        ca.acciones=di.SiguienteSignificado();
        arr.Definir(i,ca);
        di.Avanzar();
    } mergesort(arr);
    return arr;
}

void Wolfie::actualizarCotizacion(const Nombre nt, Nat cot){
    /// Ahora creo que no hay nada que se pase por copia que no deba.
    tupla1 &datos=_datosTitulo.Significado(nt);
    datos._titulo.recotizar(cot);
    DiccAcot<Cliente,datosCliente>::Iterador itDiccCli=datos._diccCli.CrearIt();
    while (itDiccCli.HaySiguiente()) {
        datosCliente &dcli=itDiccCli.SiguienteSignificado();
        Cliente c=itDiccCli.SiguienteClave();
        if (dcli._pVenta.Cardinal()>0) {
          Promesa pv=dcli._pVenta.CrearIt().Siguiente();
          if (pv.promesaEjecutable(cot,datos._titulo.cantmax()-datos._cantWolfie)) {
            _accTxCliente.Significado(c)=_accTxCliente.Significado(c)-pv.cantidad();
            dcli._acc-=pv.cantidad();
            dcli._pVenta=Conj<Promesa>();
            _promUlt=Conj<tupla2>();
            datos._cantWolfie-=pv.cantidad();
          }
        } itDiccCli.Avanzar();
    } Arreglo<tuplaCA> cliO = DiccAcot2ArrOrd(_accTxCliente);
    for (Nat i=0;i<cliO.Tamanho();i++) {
        Cliente c=cliO[i].cliente;
        datosCliente &dcli = datos._diccCli.Significado(c);
        if (dcli._pCompra.Cardinal()>0) {
          Promesa pc=dcli._pCompra.CrearIt().Siguiente();
          if (pc.promesaEjecutable(cot,datos._titulo.cantmax()-datos._cantWolfie)) {
            _accTxCliente.Significado(c)=_accTxCliente.Significado(c)+pc.cantidad();
            dcli._acc+=pc.cantidad();
            dcli._pCompra=Conj<Promesa>();
            datos._cantWolfie+=pc.cantidad();
            _promUlt=Conj<tupla2>();
          }
        }
    }
}

Nat Wolfie::cantClientes() const {
    return _clientes.Cardinal();
}

Nat Wolfie::cantTitulos() const {
    return _titulos.Cardinal();
}

void Wolfie::agregarPromesa(const Cliente c, Promesa p){
    datosCliente &datos = _datosTitulo.Significado(p.titulo())._diccCli.Significado(c);
    if (p.tipo()==vender) {
        datos._pVenta.AgregarRapido(p);
    } else {
        datos._pCompra.AgregarRapido(p);
    }

	if (!(_promUlt.EsVacio()) && (_promUlt.CrearIt().Siguiente()._cliente==c)) {
        _promUlt=Conj<tupla2>();
    }
//cout<<endl<<endl<< "PROMESA ESTA?  "<< (_datosTitulo.Significado(p.titulo())._diccCli).Significado(c)._pCompra.Pertenece(p) <<endl<<endl;
}

bool Wolfie::enAlza(Nombre nt) {
    return _datosTitulo.Significado(nt)._titulo.enalza();
}

///----Funciones del iterador de titulos----////

typename Wolfie::itTitulo Wolfie::CrearIt() const
{
    return itTitulo(this);
}

Wolfie::itTitulo::itTitulo(const Wolfie* d){
	//Wolfie w2 = Wolfie(*d);
	//itClaves = w2._titulos.CrearIt();
	//Conj<string>::const_Iterador it = d->_titulos.CrearIt();
    itClaves = d->_titulos.CrearIt();
    wolfinator = d;
}

Wolfie::itTitulo::itTitulo(const typename Wolfie::itTitulo& otro){
    itClaves=otro.itClaves;
    wolfinator = otro.wolfinator;
}


bool Wolfie::itTitulo::HaySiguiente() const{
    return itClaves.HaySiguiente();
}

Titulo Wolfie::itTitulo::Siguiente() const {
    return wolfinator->_datosTitulo.const_Significado(itClaves.Siguiente())._titulo;
}

void Wolfie::itTitulo::Avanzar(){
    itClaves.Avanzar();
}

typename Wolfie::itTitulo&  Wolfie::itTitulo::operator = (const typename Wolfie::itTitulo& otro) {
	itClaves = otro.itClaves;
    wolfinator = otro.wolfinator;
    return (*this);
}
