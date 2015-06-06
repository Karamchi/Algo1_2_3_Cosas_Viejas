#include <vector>
#include <queue>
#include "sched_rr2.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR2::SchedRR2(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	n=argn[0];
	quantums.resize(n);
	tpasado.resize(n);
	cuantas.resize(n);
	q.resize(n);
	for (int i=0;i<n;i++) {
		quantums[i]=argn[i+1];
		tpasado[i]=0;
		cuantas[i]=0;
	}
}

SchedRR2::~SchedRR2() {

}


void SchedRR2::load(int pid) {
	int min=999;
	int mincpu=999;
	for (int i=0;i<n;i++) {
		if (cuantas[i]<min) {
			min=cuantas[i];
			mincpu=i;
		}
	}
	cuantas[mincpu]++;
	q[mincpu].push(pid);
}

void SchedRR2::unblock(int pid) {
	//q.push(pid);
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
	if (m == EXIT) {
		// Empieza nuevo quantum de ese core
		tpasado[cpu]=0;
		// Si el pid actual terminó, sigue el próximo.
		if (q[cpu].empty()) return IDLE_TASK;
		int sig = q[cpu].front();
		q[cpu].pop();
		cuantas[cpu]--;
		return sig;
	} else {
		// Esta es la parte que hay que cambiar
		//Hay que ver si terminó el quantum
		//Si no terminó, pushearlo y devolver el siguiente
		if (current_pid(cpu)==IDLE_TASK && q[cpu].empty()) return IDLE_TASK;
		tpasado[cpu]++;
		if (tpasado[cpu]>=quantums[cpu]) {
			tpasado[cpu]=0;
			if (current_pid(cpu)!=IDLE_TASK) q[cpu].push(current_pid(cpu));
			int sig = q[cpu].front();
			q[cpu].pop();
			return sig;
		} return current_pid(cpu);
	}

}

int SchedRR2::next(int cpu) {
}
