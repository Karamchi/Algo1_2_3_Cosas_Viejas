#include <iostream>
#include <fstream>
#include "DiccHashCerrado.hpp"
#include "mini_test.h"

using namespace std;
using namespace aed2;

void test_Definido () {

	ASSERT(false);
}

void test_Definir () {

	ASSERT(false);
}

void test_String_Vacio () {

	ASSERT(false);
}

void test_Significado () {

	ASSERT(false);
}

void test_Borrar () {

	ASSERT(false);
}

void test_CantClaves () {

	ASSERT(false);
}

void test_claves(){
	cout << endl;

	DiccHashCerrado<int> dhi;
	Lista<String> claves;

	claves = dhi.Claves();
	cout << claves << endl;

	ASSERT( dhi.CantClaves() == 0 );

	dhi.Definir("juanca",40);
	dhi.Definir("moncho",38);

	claves = dhi.Claves();
	cout << claves << endl;

	ASSERT( dhi.CantClaves() == 2 );

	dhi.Definir("moncho",56);

	claves = dhi.Claves();
	cout << claves << endl;

	ASSERT( dhi.CantClaves() == 2 );

	dhi.Borrar("juanca");

	claves = dhi.Claves();
	cout << claves << endl;

	ASSERT( dhi.CantClaves() == 1 );

	dhi.Borrar("moncho");

	claves = dhi.Claves();
	cout << claves << endl;

	ASSERT( dhi.CantClaves() == 0 );
	cout << endl;
}

void test_colisiones(){

	DiccHashCerrado<int> dh;

//	std::string archnom = "sequences.txt"; char delim = '\n';
//	std::string archnom = "gaussian-distributions.txt"; char delim = '\n';
	std::string archnom = "casos_alumnos.txt";  char delim = '\n';
//	std::string archnom = "casos_evaluacion.txt"; char delim = '\n';


	int val = 0;
	string str;

	ifstream archin(archnom.c_str());
	while(getline(archin,str,delim) && archin.good()){

		//cout << "Definiendo: " << str << endl;
		dh.Definir(str, val);
		val++;

		//if (val == 100) break;
	}
	archin.close();

	cout << endl;
	cout << "Cantidad de elementos definidos: ";
	cout << dh.CantClaves() << endl;
	//ASSERT_EQ(dh.CantClaves(),val);

	cout << "Factor de carga: " << dh.factorCarga() << endl;
	cout << "Colisiones: " << dh.colisiones() << endl;
}

void test_redimensionado(){

	DiccHashCerrado<int> dh;

//	std::string archnom = "sequences.txt";
	std::string archnom = "gaussian-distributions.txt";

	int val = 0;
	string str;

	ifstream archin(archnom.c_str());
	while(getline(archin,str) && archin.good()){

		dh.Definir(str, val);
		val++;
	}
	archin.close();

	ASSERT_EQ(dh.CantClaves(),val);

	Nat eval = 0;
	archin.open(archnom.c_str());
	while(getline(archin,str) && archin.good()){

		ASSERT(dh.Definido(str));
		ASSERT_EQ(dh.Significado(str),eval);
		eval++;
	}
	archin.close();

	ASSERT_EQ(eval,val);
}


int main() {

	//RUN_TEST(test_Definido);
	//RUN_TEST(test_Definir);
	//RUN_TEST(test_String_Vacio);
	//RUN_TEST(test_Significado);
	//RUN_TEST(test_Borrar);
	//RUN_TEST(test_CantClaves);
	RUN_TEST(test_claves);

//	RUN_TEST(test_redimensionado);
//	RUN_TEST(test_colisiones);

	return 0;
}
