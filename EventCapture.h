//
// Created by USER on 12/4/2018.
//

#ifndef CONTINUOUSPROCESSING_EVENTCAPTURE_H
#define CONTINUOUSPROCESSING_EVENTCAPTURE_H


#include "Condition.h"
#include "ResultListener.h"
#include "DerivedEventStore.h"
#include "Process.h"
#include <queue>


class EventCapture: public Process{
private:
	//
	queue<EventPtr>* inputQueue;
	
	//the input queue of other processing unit, so this class should not maintain deallocate it memory
	queue<EventPtr> * outputQueue;
    Condition condition;
	string inputStreamName;
    string outputStreamName;
public:
	EventCapture(queue<EventPtr> * outputQueue);

	~EventCapture();

	void setCondition(Condition condition);

	void setInputStreamName(string name);

	void setOutputStreamName(string name);

	queue<EventPtr>* getInputQueue();

	void process(int timeSlice = 50);
};


#endif //CONTINUOUSPROCESSING_EVENTCAPTURE_H
