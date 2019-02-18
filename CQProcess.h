//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_CQPROCESS_H
#define CONTINUOUSPROCESSING_CQPROCESS_H


#include "Event.h"
#include "Process.h"
#include <vector>
#include "Condition.h"
#include "Operator.h"
#include "Window.h"
#include "OperatorPredicate.h"
#include "EnhanceEventResult.h"
#include <unordered_map>
#include <queue>
#include <set>

//the ResultListener return DerivedEventPtr.
class CQProcess: public Process{

private:
	string inputStreamName;
	//the result name of stream after processing
	string outputStreamName;
	queue<EventPtr> * inputQueue;
	//the input queue of other processing units.
	set<queue<EventPtr>*> outputQueueSet;
    // all stateless operatorPredicates and simple predicates share one queue reader.
	Predicate* predicate;

    //sliding window, or tumble window or others
    Window * win;
public:
	CQProcess(string outputStreamName);
	~CQProcess();

	//---------------------------
	//implemented methods
	//-------------------------
	bool process(int timeSlice);
	void addOutputQueue(queue<EventPtr> *outputQueue);
	vector<string> getInputStreamNames();
	vector<queue<EventPtr>*> getInputQueues();
	string getOutputStreamName();
   
	//--------------------------------
	//other
	//---------------------------------
    void setPredicate(Predicate * pre);
    void setOutputStreamName(string name);
	void setInputStreamName(string name);
    queue<EventPtr>* getInputQueue();
    void setWindow(Window *w);
	Predicate* getPredicate();
};
#endif //CONTINUOUSPROCESSING_CQPROCESS_H
