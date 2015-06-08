#ifndef __SCHED_RR2__
#define __SCHED_RR2__

#include <vector>
#include <queue>
#include "basesched.h"

class SchedRR2 : public SchedBase {
	public:
		SchedRR2(std::vector<int> argn);
		virtual void initialize() {};
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		std::vector<std::queue<int> > q;
		std::vector<int> quantums;
		std::vector<int> tpasado;
		std::vector<int> cuantas;
		std::vector<int> encual;
		int n;
};

#endif
