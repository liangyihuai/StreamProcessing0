//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_CEPPROCESS_H
#define CONTINUOUSPROCESSING_CEPPROCESS_H

#include "ExistOp.h"
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
#include <mutex>

using namespace std;

/*
Ŀǰ�Ǽ򵥵İ汾��CEP�����ֻ��һ�����֣������Ĳ�������������IF�ֶ����档
һ��CEP���Խ��ն�����������ݣ����е����������������ܿ������IF�ֶ������Operator�С�
ĿǰIF�ֶε�Operator��exist����Ϊ������������time length��sliding length������ͬ�ĳ��ȡ�
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
    bool process(int timeSlice);
	vector<string> getInputStreamNames();
	vector<queue<EventPtr>*> getInputQueues();
	string getOutputStreamName();
	void addOutputQueue(queue<EventPtr>* outputQueue);

	//---------------------------
	//other
	//----------------------------
    void addCondition(ExistOp * con, string inputStreamName);
    void setResultListener(ResultListener* listener);
    void setWindow(int timeWindowLen);
	void result();
	void setInputStreamNames(vector<string> names);
    
private:
	vector<ExistOp*> existOpVec;
	vector<string> inputStreamNames;
	vector<queue<EventPtr>*>* inputQueues;
	string outputStreamName;
	//queue<EventPtr> *outputQueue;
	//set up callback function to process the result of this query
	ResultListener* resultListener = nullptr;
	int windowLen = 1000; //1 second

public:
	//CEP����Ļ�������Ŀǰ���е�CEPֻ��һ�������Ժ�Ӧ�øĽ���ʹ��ÿһ��queue��һ�������Ļ�����
	static mutex mutexOfCEPResult;
};


#endif //CONTINUOUSPROCESSING_CEPPROCESS_H
