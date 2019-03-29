//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_CEPPROCESS_H
#define CONTINUOUSPROCESSING_CEPPROCESS_H

#include "../op/ExistOp.h"
#include "../common/Event.h"
#include "Process.h"
#include <queue>
#include <vector>
//#include "QueueReader.h"
#include "../expression/Condition.h"
#include "../op/inter/Operator.h"
#include "result/ResultListener.h"
#include "../expression/OperatorPredicate.h"
#include "result/MultEventResult.h"
#include <unordered_map>
#include <mutex>

using namespace std;

/*
目前是简单的版本，CEP的输出只有一个名字，其他的操作都用在条件IF字段里面。
一个CEP可以接收多个输入流数据，所有的数据流都被尽可能快地输入IF字段里面的Operator中。
目前IF字段的Operator以exist操作为主，并且它的time length和sliding length具有相同的长度。
The ResultListener return vector<DerivedEventPtr>.
*/
class CEPProcess: public Process{
public:
	CEPProcess(vector<string> inputStreamNames, string outputStreamName);
	~CEPProcess();
	//------------------------
	//implemented methods
	//------------------------------
	/*insert event to the window of operator from input queues.
	this function is called by a time scheduler*/
    bool process(int timeSlice) override;
	vector<string> getInputStreamNames()override;
	vector<queue<EventPtr>*> getInputQueues()override;
	string getOutputStreamName()override;
	void addOutputQueue(queue<EventPtr>* outputQueue, string outputStreamNameOfProcess)override;
	set<string> getConnectedOutputNameSet()override;

	//---------------------------
	//other
	//----------------------------
    void setResultListener(ResultListener<EventPtr>* listener);
	void result();
	void setInputStreamNames(vector<string> names);
    
private:
	vector<Window<bool>*> timeSlidingWinForExistOpVec;
	vector<string> inputStreamNames;
	vector<queue<EventPtr>*>* inputQueues;
	string outputStreamName;

	//set up callback function to process the result of this query
	ResultListener<EventPtr>* resultListener = nullptr;
	const int windowLen = 1000; //1 second

public:
	//CEP结果的互斥锁，目前所有的CEP只有一个锁，以后应该改进，使得每一个queue有一个单独的互斥锁
	static mutex mutexOfCEPResult;
};

#endif //CONTINUOUSPROCESSING_CEPPROCESS_H
