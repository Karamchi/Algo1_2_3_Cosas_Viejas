#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	int n=argn[0];
	quantums.resize(n);
	tpasado.resize(n);
	for (int i=0;i<n;i++) {
		quantums[i]=argn[i+1];
		tpasado[i]=0;
	}
}

void SchedRR::load(int pid) {
	q.push(pid);	
}

void SchedRR::unblock(int pid) {
	q.push(pid);
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	if (m == EXIT || m==BLOCK) {
		// Empieza nuevo quantum de ese core
		tpasado[cpu]=0;
		// Si el pid actual terminó, sigue el próximo.
		if (q.empty()) return IDLE_TASK;
		int sig = q.front();
		q.pop();
		return sig;
	} else {
		// Esta es la parte que hay que cambiar
		//Hay que ver si terminó el quantum
		//Si no terminó, pushearlo y devolver el siguiente
		if (current_pid(cpu)==IDLE_TASK && q.empty()) return IDLE_TASK;
		tpasado[cpu]++;
		if (tpasado[cpu]>=quantums[cpu] || current_pid(cpu)==IDLE_TASK) {
			tpasado[cpu]=0;
			if (current_pid(cpu)!=IDLE_TASK) q.push(current_pid(cpu));
			int sig = q.front();
			q.pop();
			return sig;
		} return current_pid(cpu);
	}

}
