//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_CEPPROCESS_H
#define CONTINUOUSPROCESSING_CEPPROCESS_H

#include "Event.h"
#include "Process.h"
#include <queue>
#include <vector>
//#include "QueueReader.h"
#include "Condition.h"
#include "Operator.h"
#include "ResultListener.h"
#include "WindowBase.h"
#include "OperatorPredicate.h"
#include "MulStreamResult.h"
#include <unordered_map>


using namespace std;

//the ResultListener return vector<DerivedEventPtr>.
//复杂事件处理基于时间窗口或者计数窗口。格式为[time len, time sliding] or [count len, count sliding].
//len表示
class CEPProcess: public Process{
private:
    //one row of predicates are associating with a window.
	vector<vector<Predicate*>*> predicateMatrix;
	
	vector<string> inputStreamNames;

	vector<queue<EventPtr>*>* inputQueues;

	string outputStreamName;

	queue<EventPtr> *outputQueue;

	vector<WindowBase*> windowVec;//the initial values are nullptr

    //set up callback function to process the result of this query
    ResultListener* resultListener = nullptr;

	//output target names
    vector<string> resultStreams;

	//length and sliding of count window equal to 3
	const int DEFAULT_COUNT_LEN_SLIDING = 3;

	const int MAX_READER = 10;

	WindowBase * window = nullptr;
public:
	CEPProcess(int inputStreamNum, string outputStreamName, queue<EventPtr>* outputQueue);

    //only class execution/ExecuteSchedule could access this method
    //before call it, the queue readers should be prepared.
    void process(int timeSlice);
    void addPredicate(Predicate * pre, string stream);
    void setResultListener(ResultListener* listener);
    void setWindow(WindowBase *w);
	WindowBase * getWindow() {return this->window;}

	void setInputStreamNames(vector<string> names) {
		this->inputStreamNames = names;
	}

	vector<queue<EventPtr>*>* getInputQueues() {
		return this->inputQueues;
	}

    ~CEPProcess();
};


#endif //CONTINUOUSPROCESSING_CEPPROCESS_H
