#ifndef CONTINUOUSPROCESSING_EXECUTESCHEDULER_H
#define CONTINUOUSPROCESSING_EXECUTESCHEDULER_H


#include "DerivedEventStore.h"
#include <unordered_map>
#include "EventProcess.h"
#include "EventCapture.h"
#include "CQProcess.h"
#include "CEPProcess.h"
#include "Process.h"

/*
维护一个输入队列不为空的cp队列，循环消费cp中输入队列中的数据，直到cp队列为空。
1. 在输入队列不为空的时候，将相应的队列加入cp队列中
2. 不断从cp队列头部弹出一个cp，消费cp的输入队列timeSlice个数据或者队列为空。如果消费了timeSlice个数据之后，该队列不为空，
就将其添加到cp队列的尾部。如果该cp有多个输入队列，只要有一个队列为空，就不将该cp加入cp队列中。
*/
class ExecuteScheduler {
private:
	static std::queue<Process*> processQueue;
	static std::set<Process*> processSet;//avoid duplicated objects in processQueue

	static EventProcess *eventProcess;

	//output stream name -> process
	static std::unordered_map<string, Process*> processMap;

	static set<CEPProcess*> cepSet;

	//connect process unit A and B. It is used to build compute graph
	static void addProcessUnitToGraph(string inputStreamNameOfB, 
							queue<EventPtr> * inputQueueOfB, string outputNameOfB);

	static void addProcessUnitToGraph(Process* processOfB);

	//check whether the outputQueue reference of a process is nullptr.
	static void checkGraph();

public:
	static void registerEventProcess(EventProcess* e);

	static void registerProcess(string outputStreamName, Process *p);

	static void initialize();

	static void runProcessQueue();

	static void pushBackProcessQueue(Process * cp);

	static void buildGraph();

	static void updateGraph();

	static EventProcess* getEventProcess();

	static void addCEP(CEPProcess * p);

	static set<CEPProcess*> getCEPs();

	static bool deleteProcess(string outputStreamName);

	static Process * getProcess(string outputStreamName);

public:
	//process unit的互斥锁
	static mutex mutexOfProcessMap;
};

#endif //CONTINUOUSPROCESSING_EXECUTESCHEDULER_H