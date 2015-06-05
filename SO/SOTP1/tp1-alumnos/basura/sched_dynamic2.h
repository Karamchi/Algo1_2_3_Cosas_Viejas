#ifndef __SCHED_DYNAMIC_
#define __SCHED_DYNAMIC_

#include <vector>
#include <queue>
#include <algorithm>
#include "basesched.h"

using namespace std;

class SchedDynamic : public SchedBase {
	public:
		SchedDynamic(std::vector<int> argn);
        	~SchedDynamic();
		virtual void initialize();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > > q;
		vector<int> rates;
};

#endif
