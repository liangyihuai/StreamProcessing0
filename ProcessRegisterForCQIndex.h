#pragma once

#include "Process.h"
#include <vector>
#include <list>

class ProcessRegisterForCQIndex {
public:
	static Process * getProcess(int index);

	static list<Process*> getProcess(vector<int64_t> indexes);

	static void addProcess(Process*);

	static bool deleteProcess(int index);

	static bool deleteProcess(Process*);



private:
	static vector<Process*> processVector;

};