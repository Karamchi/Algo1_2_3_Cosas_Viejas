#include <vector>
#include <queue>
#include <iostream>
#include "sched_fixed.h"

using namespace std;

SchedFixed::SchedFixed(vector<int> argn) {
}

void SchedFixed::initialize() {
	int n=total_tasks();
	for(int i=0;i<n;i++){
		rates.push_back(period(i));
	}
}

void SchedFixed::load(int pid) {
	q.push(make_pair(rates[pid],pid)); // llegó una tarea nueva
}

void SchedFixed::unblock(int pid) {
}

int SchedFixed::tick(int cpu, const enum Motivo m) {
	if (m == EXIT) {
		// Si el pid actual terminó, sigue el próximo.
		if (q.empty()) 
			return IDLE_TASK;
		else {
			int sig = q.top().second;
			q.pop();
			return sig;
		}
	} else {
		// Siempre sigue el pid actual mientras no termine.
		if (current_pid(cpu) == IDLE_TASK && !q.empty()) {
			int sig = q.top().second;
			q.pop();
			return sig;
		} else {
		//pero en cada tick tenés que ver si no lodeaste una que tenga más prioridad que la que estabas ejecutando
			int c=current_pid(cpu);
			int act=rates[c];
			if (act<=q.top().first)
				return c;
			else {
				q.push(make_pair(act,c));
				int sig = q.top().second;
				q.pop();
				return sig;
			}
		}
	}
}

