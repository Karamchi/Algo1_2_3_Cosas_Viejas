#ifndef MESSINERIA_H_
#define MESSINERIA_H_

#include <iostream>
#include <cassert>
using namespace std;

/*
 * Se puede asumir que el tipo T tiene constructor por copia y operator==
 * No se puede asumir que el tipo T tenga operator=
 */
template<typename T>
class Messineria {

  public:

	/*
	 * Crea una secta nueva sin adeptos.
	 */
	Messineria();

	/*
	 * Una vez copiada, ambas Messinerias deben ser independientes,
	 * es decir, cuando se borre una no debe borrar la otra.
	 */
	Messineria(const Messineria<T>&);

	/*
	 * Acordarse de liberar toda la memoria!
	 */
	~Messineria();

	/*
	 * Agrega un nuevo adepto a la Messineria. Si ya tenemos al Elegido
	 * el nuevo adepto deberá arrodillarse a la izquierda de él. En caso
	 * contrario, se arrodillará a la izquierda del que está alabando.
	 */
	void golDeMessi(const T&);

	/*
	 * Elimina de la secta al adepto pasado por parámetro. Si el mismo tenía
	 * el turno de alabar, debe pasar al siguiente (en caso de que haya).
	 */
	void golDeCristiano(const T&);

	/*
	 * Devuelve el adepto que está albando.
	 *
	 * PRE: Hay adeptos en la Messineria.
	 */
	const T& adeptoAlabando() const;

    /*
	 * Devuelve el próximo elemento según el orden dado.
	 * Quien alaba debe cambiar. Con lo cual sucesivas llamadas a esta función
	 * retornan distintos valores.
	 *
	 * PRE: Hay adeptos en la Messineria.
	 */
	const T& alabarMessi();

	/*
	 * Cambia el turno de alabar al inmediato anterior.
	 *
	 */
	void olvideAlabarloUnPocoMas();

	/*
	 * Selecciona al adepto que está alabando como el Elegido.
	 *
	 * PRE: Hay adeptos en la Messineria y no hay Elegido.
	 */
	void escogerElegido();

    /*
	 * Indica si esta presente el Elegido entre los adeptos.
	 */
	bool hayElegido() const;

	/*
	* Elimina de la secta al Elegido.
	*
	* PRE: hay Elegido en la Messinería.
	*/
	void traidor();

	/*
	* El Elegido interrumpe el tuno y pasa a ser el que está alabando
	*
	* PRE: hay Elegido en la Messinería.
	*/
	void interrumpirTurno();

	/*
	 * Devuelve al Elegido.
	 *
	 * PRE: Hay Elegido en la Messineria.
	 */
	const T& dameElegido() const;

	/*
	 * Dice si la Messineria tiene o no adeptos.
	 */
	bool esVacia() const;

	/*
	 * Devuelve la cantidad de adeptos a la Messineria.
	 */
	int tamanio() const;

	/*
	 * Devuelve true si las Messinerias son iguales.
	 */
	bool operator==(const Messineria<T>&) const;

	/*
	 * Debe mostrar la ronda por el ostream (y retornar el mismo).
	 * Messineria vacio: []
	 * Messineria con 2 elementos (e1 es el actual): [e1, e2]
	 * Messineria con 2 elementos (e2 es el actual y e1 es el Elegido): [e2, e1*]
	 * Messineria con 3 elementos (e1 es el actual, e2 fue agregado izqes que e3,
	 * e1 fue agregado antes que e2): [e1, e2, e3]
	 */
	ostream& mostrarMessineria(ostream&) const;


  private:
	/*
	 * No se puede modificar esta funcion.
	 */
	Messineria<T>& operator=(const Messineria<T>& otra) {
		assert(false);
		return *this;
	}

	/*
	 * Aca va la implementación del nodo.
	 */
	struct Nodo {
		Nodo* izq;
		T adepto;
		Nodo* der;
		Nodo(const T& d) : izq(), der(), adepto(d) {
        };
	};

    int len;
	Nodo* reza;
    Nodo* eleg;
    Nodo* interrumpe;
    bool pertenece(const T&) const;
};

template<class T>
ostream& operator<<(ostream& out, const Messineria<T>& a) {
	return a.mostrarMessineria(out);
}

// Implementación a hacer por los alumnos.




template<class T>
Messineria<T>::Messineria()
{
reza=NULL;
eleg=NULL;
interrumpe=NULL;
len = 0;
}


template<class T>
Messineria<T>::Messineria(const Messineria<T>& m2){
    this->reza=NULL;
    this->eleg=NULL;
    this->interrumpe=NULL;
    len = 0;
    if (!(m2.esVacia())) {
        Nodo* a=m2.reza;
        golDeMessi(a->adepto);
        a=(a->der);
        while (a != m2.reza) {
            golDeMessi(a->adepto);
            a=a->der;
        }
        if (m2.hayElegido())
        {
            Nodo* b = m2.reza;
            if (m2.eleg==b) {
                escogerElegido();
            }
            else
            {
                b=b->der;
                alabarMessi();
                while ((this->reza)!=m2.reza)
                {
                    if (m2.eleg==b) {
                        escogerElegido();
                    }
                    b=b->der;
                    alabarMessi();
                }
            }
        } else
        {
            Nodo* b = m2.reza;
            while ((this->reza)->adepto!=m2.reza->adepto)
            {
                    b=b->der;
                    alabarMessi();
            }
        }
    }
    if (m2.interrumpe!=NULL) {
        this->interrumpe=this->eleg;
    }
}

template<class T>
 Messineria<T>::~Messineria(){
    if (!(esVacia())){
        int l=len;
        if (l>2) {
            Nodo* a;
            a=(reza->izq)->izq;
            while (l>2) {
              delete a->der;
              a=a->izq;
              l--;
            }
        }
        if (l == 2){
            delete ((this->reza)->der);
            l--;
        }
        if (l==1){
            delete (this->reza);
            l--;
        }
    }
    len=0;
    eleg=NULL;
    interrumpe=NULL;
    reza=NULL;
}


template<class T>
void Messineria<T>::golDeMessi(const T& adnuevo){
    if (pertenece(adnuevo)) return;

    Nodo* nuevo = new Nodo(adnuevo);
    if(esVacia())
    {
        this->reza=nuevo;
        nuevo->izq=nuevo;
        nuevo->der=nuevo;
    }
    if(tamanio() == 1)
    {
        nuevo->izq=(this->reza);
        nuevo->der=(this->reza);
        (this->reza)->izq=nuevo;
        (this->reza)->der=nuevo;
    }
    if(tamanio() > 1)
    {
        if (hayElegido())
        {
            nuevo->izq=(this->eleg)->izq;
            nuevo->der=this->eleg;
            ((this->eleg)->izq)->der=nuevo;
            (this->eleg)->izq=nuevo;
        }
        else
        {
            nuevo->izq=(this->reza)->izq;
            nuevo->der=this->reza;
            ((this->reza)->izq)->der=nuevo;
            (this->reza)->izq=nuevo;
        }
    }
    len++;
}

template<class T>
void Messineria<T>::golDeCristiano(const T& seVa){
    assert(pertenece(seVa));
    if(len==1){
        delete this->reza;
        this->eleg = NULL;
        len=0;
    } else {
        if((hayElegido()) && ((this->eleg)->adepto==seVa))
        {
            if ((this->reza)==this->eleg) {
                this->reza=(this->reza)->der;
            }
            this->eleg->izq->der=this->eleg->der;
            this->eleg->der->izq=this->eleg->izq;
            delete this->eleg;
            this->eleg = NULL;
            this->interrumpe=NULL;
        } else {
            Nodo* a=this->reza;
            if ((this->reza)->adepto==seVa) {
                this->reza=(this->reza)->der;
                (a->izq)->der=a->der;
                (a->der)->izq=a->izq;
                delete a;
                a=NULL;
            } else {
                a=a->der;
                bool listo=false;
                while (!listo) {
                    if (a->adepto==seVa) {
                        (a->izq)->der=a->der;
                        (a->der)->izq=a->izq;
                        delete a;
                        a=NULL;
                        listo=true;
                    } else{a=a->der;}
                }
            }
        } len--;
    }
}


template<class T>
const T& Messineria<T>::adeptoAlabando() const{
    assert(!(esVacia()));
    if(this->interrumpe!=NULL)
    {
        return (this->interrumpe)->adepto;
    }
    else
    {
        return(this->reza->adepto);
    }
}


template<class T>
const T& Messineria<T>::alabarMessi(){
    assert(!(esVacia()));
    if((this->interrumpe)!=NULL)
    {
        this->interrumpe=NULL;
    }
    else
    {
        this->reza=this->reza->der;
    }
    return (this->reza)->adepto;
}


template<class T>
void Messineria<T>::olvideAlabarloUnPocoMas(){
    assert(!(esVacia()));
    this->reza=(this->reza)->izq;
    this->interrumpe=NULL;
}


template<class T>
void Messineria<T>::escogerElegido(){
    assert(!(esVacia()));
    this->eleg=this->reza;
}


template<class T>
bool Messineria<T>::hayElegido() const{
    return ((this->eleg)!=NULL);
};

template<class T>
void Messineria<T>::traidor(){
    assert(hayElegido());
    if (tamanio()==1){
        this->reza=NULL;
    } else {
        if ((this->reza)==this->eleg) {
            this->reza=(this->reza)->der;
        }
        ((this->eleg)->izq)->der=(this->eleg)->der;
        ((this->eleg)->der)->izq=(this->eleg)->izq;
    }
    delete this->eleg;
    this -> eleg = NULL;
    this -> interrumpe = NULL;
    len--;
}


template<class T>
void Messineria<T>::interrumpirTurno(){
    assert(hayElegido());
    this->interrumpe=this->eleg;

}


template<class T>
const T& Messineria<T>::dameElegido() const{
    assert(hayElegido());
    return ((this->eleg)->adepto);
}

template<class T>
bool Messineria<T>::esVacia() const{
    return len == 0;
}



template<class T>
int Messineria<T>::tamanio() const{
    return len;
}



template<class T>
bool Messineria<T>::operator==(const Messineria <T>& m2) const{
    //if (m2.esVacia()!= esVacia()) return false;
    //if (esVacia()) return true;
    //// ambas no son vacias.
    bool res=true;
    if (m2.esVacia()||esVacia()){
        if ((m2.esVacia())!= esVacia()){
            res=false;
        }
    } else {
        if (m2.hayElegido() && hayElegido()) {
            if ((this->eleg->adepto)!=m2.eleg->adepto) {
                res=false;
            } if (((this->interrumpe)==NULL) != (m2.interrumpe==NULL)) {
                res=false;
            }
        }
        if (m2.hayElegido()!= hayElegido())
        {
            res=false;
        }
        Nodo* a=this->reza;
        Nodo* b=m2.reza;
        if (a->adepto!=b->adepto){
            res=false;
        } else {
            a=a->der;
            b=b->der;
            while (a!=this->reza){
                if (a->adepto!=b->adepto) {
                    res=false;
                    a=this->reza;
                } else {
                    a=a->der;
                    b=b->der;
                }
            }
        }
    } return res;
}



template<class T>
ostream& Messineria<T>::mostrarMessineria(ostream& os) const{
    if (esVacia()) {
        os<<"[]";
    } else {
        Nodo* a=this->reza;
        os <<"[";
        if (interrumpe!=NULL) {
            os << this->eleg->adepto << "*, ";
        }
        if(this-> eleg != a)
            {
            os << a->adepto;
            }
        else
            {
            os << a->adepto << "*";
            }
        a=a->der;
        while (a!=(this->reza)) {
            if(this-> eleg != a)
                {os << ", " << a->adepto;}
            else {
                if (interrumpe==NULL)
                    {os << ", " << a->adepto << "*";}
            }
            a=a->der;
        }
        os << "]";
    }
    return os;
}

    template<class T>
    bool Messineria<T>::pertenece(const T& a) const{
        bool res=false;
        Nodo* b=this->reza;
        int l=0;
        while (l<len) {
            if (b->adepto==a) {
                res=true;
            }
            b=b->der;
            l++;
        } return res;
    }
#endif //MESSINERIA_H_
