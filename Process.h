#pragma once
//the interface of process, including event filter, event capture, cq, cep

#include "Event.h"
#include <vector>
#include <queue>
#include <iostream>

class Process {
public:
	/*insert event to the window of operator from input queues.
	this function is called by a time scheduler. 
	Return false, the process needs to push back to the CP queue.
	*/
	virtual bool process(int timeSlice) = 0;

	virtual vector<string> getInputStreamNames() = 0;

	virtual vector<queue<EventPtr>*> getInputQueues() = 0;

	virtual string getOutputStreamName() = 0;

	virtual void addOutputQueue(queue<EventPtr>* outputQueue) = 0;
};


