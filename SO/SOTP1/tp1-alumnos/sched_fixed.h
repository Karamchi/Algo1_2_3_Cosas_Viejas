#ifndef __SCHED_FIXED__
#define __SCHED_FIXED__

#include <vector>
#include <queue>
#include <algorithm>
#include "basesched.h"

using namespace std;

class SchedFixed : public SchedBase {
	public:
		SchedFixed(std::vector<int> argn);
		virtual void initialize();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);	
	private:
		priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > > q;
		vector<int> rates;
};

#endif
