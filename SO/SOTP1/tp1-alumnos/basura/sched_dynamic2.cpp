#include <vector>
#include <queue>
#include <iostream>
#include "sched_dynamic.h"

using namespace std;

SchedDynamic::SchedDynamic(vector<int> argn) {
}

SchedDynamic::~SchedDynamic() {
}

void SchedDynamic::initialize() {
	int n=total_tasks();
	for(int i=0;i<n;i++){
		rates.push_back(period(i));
	}
}

void SchedDynamic::load(int pid) {
//	q.push(make_pair(period(pid)-current_time()%period(pid),pid)); // O solo period?
	q.push(make_pair(period(pid),pid)); // O sea, lodea en múltiplos de period?
}

void SchedDynamic::unblock(int pid) {
}

int SchedDynamic::tick(int cpu, const enum Motivo m) {

	for (unsigned int i=0;i<q.size();i++) {
		q[i].first--;
	}

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
			int c=current_pid(cpu);
			int p=period(c);
			int nextreq=p-p%current_time();
			if (nextreq<=q.top().first)
				return c;
			else {
				q.push(make_pair(p,c));
				int sig = q.top().second;
				q.pop();
				return sig;		
			}
		}
	}	
	return -2;
}

/*int char type(int pid);
unsigned int declared_cputime(int pid);

tiempo restante hasta la próxima vez que salga otra tarea de ese tipo:
se crea una tarea del tipo a en k.period(pid)
luego current_time()%period(pid) da el tiempo transcurrido desde la ultima llamada
luego period-eso da cuanto falta para el próximo request
no hace falta actualizar la cola de prioridad cada tick, porque en todos baja en 1
solo cuando loadeás*/


