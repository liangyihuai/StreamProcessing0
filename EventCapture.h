#ifndef CONTINUOUSPROCESSING_EVENTCAPTURE_H
#define CONTINUOUSPROCESSING_EVENTCAPTURE_H


#include "Condition.h"
#include "ResultListener.h"
#include "DerivedEventStore.h"
#include "Process.h"
#include <queue>
#include <set>


class EventCapture: public Process{
private:
	//
	queue<EventPtr>* inputQueue;
	
	//the input queue of other processing unit, so this class should not maintain deallocate it memory
	set<queue<EventPtr>*> outputQueueSet;
    Condition condition;
	string inputStreamName;
    string outputStreamName;
public:
	EventCapture(string _outputStreamName);
	~EventCapture();

	//---------------------------
	//implemented methods
	//---------------------------
	bool process(int timeSlice = 100);
	vector<string> getInputStreamNames();
	vector<queue<EventPtr>*> getInputQueues();
	string getOutputStreamName();
	void addOutputQueue(queue<EventPtr> * outputQueue);

	//--------------------------
	//other methods
	//---------------------------
	void setCondition(Condition condition);
	void setInputStreamName(string name);
	void setOutputStreamName(string name);
	queue<EventPtr>* getInputQueue();
};

#endif //CONTINUOUSPROCESSING_EVENTCAPTURE_H
