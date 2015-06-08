#include <vector>
#include <queue>
#include <iostream>
#include "sched_dynamic.h"

using namespace std;

void insOrd(list<pair<int,int> >& q, int pid, int per);

SchedDynamic::SchedDynamic(vector<int> argn) {
}

SchedDynamic::~SchedDynamic() {
}

void SchedDynamic::initialize() {
}

void SchedDynamic::load(int pid) {
	insOrd(q,period(pid),pid);
}

void SchedDynamic::unblock(int pid) {
}

int SchedDynamic::tick(int cpu, const enum Motivo m) {

	for (list<pair<int,int> >::iterator it=q.begin();it!=q.end();it++) {
		(*it).first--;
	} nextreq--;

	if (m == EXIT) {
		// Si el pid actual terminó, sigue el próximo.
		if (q.empty()) 
			return IDLE_TASK;
		else {
			int sig = q.front().second;
			nextreq = q.front().first;
			q.pop_front();
			return sig;
		}
	} else {
		// Siempre sigue el pid actual mientras no termine.
		if (current_pid(cpu) == IDLE_TASK && !q.empty()) {
			int sig = q.front().second;
			q.pop_front();
			return sig;
		} else {
		//pero en cada tick tenés que ver si no lodeaste una que tenga más prioridad que la que estabas ejecutando
			if (nextreq<=q.front().first)
				return current_pid(cpu);
			else {
				insOrd(q,nextreq,current_pid(cpu));
				int sig = q.front().second;
				nextreq = q.front().first;
				q.pop_front();
				return sig;
			}
		}
	}	
	return -2;
}

void insOrd(list<pair<int,int> >& q, int per, int pid) {
	list<pair<int,int> >::iterator it;
	for (it=q.begin();it!=q.end();it++) {
		if (per<(*it).first) {
			q.insert(it,make_pair(per,pid));
			return;
		}
	} q.insert(it,make_pair(per,pid));
}
