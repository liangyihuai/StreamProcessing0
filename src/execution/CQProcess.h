//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_CQPROCESS_H
#define CONTINUOUSPROCESSING_CQPROCESS_H


#include "../common/Event.h"
#include "Process.h"
#include <vector>
#include "../expression/Condition.h"
#include "../op/inter/Operator.h"
#include "../expression/OperatorPredicate.h"
#include <unordered_map>
#include <queue>
#include <set>

//the ResultListener return DerivedEventPtr.
class CQProcess: public Process{
public:
	CQProcess(string outputStreamName);
	~CQProcess();

	//---------------------------
	//implemented methods
	//-------------------------
	bool process(int timeSlice)override;
	//string outputStreamNameOfProcess, the output stream name connected to this process unit.
	void addOutputQueue(queue<EventPtr> *outputQueue, string outputStreamNameOfProcess)override;
	vector<string> getInputStreamNames()override;
	vector<queue<EventPtr>*> getInputQueues()override;
	string getOutputStreamName()override;
	set<string> getConnectedOutputNameSet()override;
   
	//--------------------------------
	//other
	//---------------------------------
    void setPredicate(Predicate * pre);
    void setOutputStreamName(string name);
	void setInputStreamName(string name);
    queue<EventPtr>* getInputQueue();
    //void setWindow(Window *w);
	Predicate* getPredicate();
	void addEventToQueue(EventPtr e);

private:
	string inputStreamName;
	//the result name of stream after processing
	string outputStreamName;
	queue<EventPtr> * inputQueue;
	//the input queue of other processing units.
	set<queue<EventPtr>*> outputQueueSet;
	//the output names of process that connects to this process unit.
	set<string> connectedOutputNameSet;
	// all stateless operatorPredicates and simple predicates share one queue reader.
	Predicate* predicate;
};
#endif //CONTINUOUSPROCESSING_CQPROCESS_H
