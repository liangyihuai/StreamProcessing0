#pragma once

#include "../op/ExistOp.h"
#include "../common/Event.h"
#include "Process.h"
#include <queue>
#include <vector>
#include "../expression/Condition.h"
#include "../op/inter/Operator.h"
#include "result/ResultListener.h"
#include "../expression/OperatorPredicate.h"
#include "result/MultEventResult.h"
#include <unordered_map>
#include <mutex>
#include "ExecuteScheduler.h"

using namespace std;

/*
Ŀǰ�Ǽ򵥵İ汾��CEP�����ֻ��һ�����֣������Ĳ�������������IF�ֶ����档
һ��CEP���Խ��ն�����������ݣ����е����������������ܿ������IF�ֶ������Operator�С�
ĿǰIF�ֶε�Operator��exist����Ϊ������������time length��sliding length������ͬ�ĳ��ȡ�
The ResultListener return vector<DerivedEventPtr>.
*/
class CEPProcess: public Process{
	friend class ExecuteScheduler;
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
	//Process unit B connects to A downstream. It means that the input of B is from A.
	bool removeOutputQueueAndNameFromA(string outputNameOfProcessUnitB) override;
	bool removeAllDownStreamQueuesAndNames()override;

	//---------------------------
	//other
	//----------------------------
    void setResultListener(ResultListener* listener);
	void result();
	void setInputStreamNames(vector<string> names);
	void setPredicates(vector<Predicate*> preList);
	void setWindows(vector<Window*> windowList);
    
private:
	vector<Window*> windowList;
	vector<Predicate*> predicates;
	vector<string> inputStreamNames;
	vector<queue<EventPtr>*>* inputQueues;
	string outputStreamName;


	//set up callback function to process the result of this query
	ResultListener* resultListener = nullptr;
	const int windowLen = 1000; //1 second
};

