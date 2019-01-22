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

/*
Ŀǰ�Ǽ򵥵İ汾��CEP�����ֻ��һ�����֣������Ĳ�������������IF�ֶ����档
һ��CEP���Խ��ն�����������ݣ����е����������������ܿ������IF�ֶ������Operator�С�
ĿǰIF�ֶε�Operator��exist����Ϊ������������time length��sliding length������ͬ�ĳ��ȡ�
The ResultListener return vector<DerivedEventPtr>.
*/
class CEPProcess: public Process{
public:
	CEPProcess(int inputStreamNum, string outputStreamName, queue<EventPtr>* outputQueue);

	/*insert event to the window of operator from input queues.
	this function is called by a time scheduler*/
    void process(int timeSlice);

    void addCondition(ExistOp * con, string inputStreamName);
    void setResultListener(ResultListener* listener);
    void setWindow(int timeWindowLen);

	void result();

	void setInputStreamNames(vector<string> names) {
		this->inputStreamNames = names;
	}

	vector<string> getInputStreamNames() {
		return inputStreamNames;
	}

	vector<queue<EventPtr>*>* getInputQueues() {
		return this->inputQueues;
	}

    ~CEPProcess();

private:
	vector<ExistOp*> existOpVec;

	vector<string> inputStreamNames;
	vector<queue<EventPtr>*>* inputQueues;
	string outputStreamName;
	//queue<EventPtr> *outputQueue;

	//set up callback function to process the result of this query
	ResultListener* resultListener = nullptr;

	int windowLen = 1000; //1 second
};


#endif //CONTINUOUSPROCESSING_CEPPROCESS_H
