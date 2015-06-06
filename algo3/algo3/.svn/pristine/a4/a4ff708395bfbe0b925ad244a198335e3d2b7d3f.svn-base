#include "tasks.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

void TaskCPU(int pid, vector<int> params) { // params: n
	uso_CPU(pid, params[0]); // Uso el CPU n milisegundos.
}

void TaskIO(int pid, vector<int> params) { // params: ms_pid, ms_io,
	uso_CPU(pid, params[0]); // Uso el CPU ms_pid milisegundos.
	uso_IO(pid, params[1]); // Uso IO ms_io milisegundos.
}

void TaskAlterno(int pid, vector<int> params) { // params: ms_pid, ms_io, ms_pid, ...
	for(int i = 0; i < (int)params.size(); i++) {
		if (i % 2 == 0) uso_CPU(pid, params[i]);
		else uso_IO(pid, params[i]);
	}
}

void TaskConBloqueo(int pid, vector<int> params) {
	int tiempo = params[0];
	int inicioBloq = params[1];
	int finBloq = params[2];

	if(inicioBloq > tiempo){
		uso_CPU(pid, tiempo);
	}else{
		uso_CPU(pid,inicioBloq-2);
		uso_IO(pid,finBloq-inicioBloq+1);
		uso_CPU(pid,tiempo-finBloq);
	}
}

void TaskConsola(int pid, vector<int> params) {
	int n = params[0];
	int bmin = params[1];
	int bmax = params[2];

	for (int i=0;i<n;i++)
		uso_IO(pid,rand()%(bmax-bmin)+bmax);
}


void TaskBatch(int pid, vector<int> params) {
	int totalcpu = params[0];
	int cantbloqueos = params[1];
	vector<int> momentos(cantbloqueos); //Un array sirve pero tira un warning

	for (int i=0;i<cantbloqueos;i++) {
		momentos[i]=totalcpu; //Poco elegante pero funciona
		int agr=rand()%(totalcpu-1)+1;
		for (int j=0;j<=i;j++) { //insertar ordenado
			if (agr<momentos[j]) {
				int sw=momentos[j];
				momentos[j]=agr;
				agr=sw;
			}
			else if (agr==momentos[j]) {
				i--;
				j=i+1;
			}
		} 
	} 
/*	for (int i=0;i<cantbloqueos;i++) {
		cout << momentos[i] << ' ';
	} cout << endl;
*/
	for (int i=0;i<cantbloqueos;i++) {
		int inicioBloq = (i!=0)*momentos[i-1]; //es un if
		int finBloq = momentos[i];
//		cout << "Usando CPU..." << finBloq-inicioBloq-1 << endl;
		uso_CPU(pid,finBloq-inicioBloq-1);
//		cout << "Bloqueando..." << 1 << endl;
		uso_IO(pid,1);
	}
//		cout << "Usando CPU..." << totalcpu-momentos[cantbloqueos-1]-1  << endl;
	uso_CPU(pid,totalcpu-momentos[cantbloqueos-1]-1);
}

void tasks_init(void) {
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
	register_task(TaskConBloqueo,3);

	register_task(TaskConsola,3);
	register_task(TaskBatch,2);
}
