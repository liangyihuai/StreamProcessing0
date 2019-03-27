#ifndef CONTINUOUSPROCESSING_EVENTCAPTURE_H
#define CONTINUOUSPROCESSING_EVENTCAPTURE_H


#include "../expression/Condition.h"
#include "result/ResultListener.h"
#include "../buffer/DerivedEventStore.h"
#include "Process.h"
#include <queue>
#include <set>


class EventCapture: public Process{
private:
	//
	queue<EventPtr>* inputQueue;
	
	//the input queue of other processing unit, so this class should not maintain deallocate it memory
	set<queue<EventPtr>*> outputQueueSet;
	//the output names of process that connects to this process unit.
	set<string> connectedOutputNameSet;

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
	//string outputStreamNameOfProcess, the output stream name connected to this process unit.
	void addOutputQueue(queue<EventPtr> * outputQueue, string outputStreamNameOfProcess);

	//--------------------------
	//other methods
	//---------------------------
	void setCondition(Condition condition);
	void setInputStreamName(string name);
	void setOutputStreamName(string name);
	queue<EventPtr>* getInputQueue();

	set<string> getConnectedOutputNameSet();
};

#endif //CONTINUOUSPROCESSING_EVENTCAPTURE_H