#pragma once
//the interface of process, including event filter, event capture, cq, cep

#include "../common/Event.h"
#include <vector>
#include <queue>
#include <iostream>

class Process {
public:
	/*insert event to the window of operator from input queues.
	this function is called by a time scheduler. 
	Return false, the process needs to push back to the CP queue.*/
	virtual bool process(int timeSlice) = 0;

	virtual vector<string> getInputStreamNames() = 0;

	virtual vector<queue<EventPtr>*> getInputQueues() = 0;

	virtual string getOutputStreamName() = 0;

	//string outputStreamNameOfProcess, the output stream name connected to this process unit.
	virtual void addOutputQueue(queue<EventPtr>* outputQueue, string outputStreamNameOfProcess) = 0;

	//The current process unit might be referenced by others. 
	//Hereby, we get the outputName of those other process units.
	virtual set<string> getConnectedOutputNameSet() = 0;
};