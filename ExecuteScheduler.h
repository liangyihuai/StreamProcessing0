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
ά��һ��������в�Ϊ�յ�cp���У�ѭ������cp����������е����ݣ�ֱ��cp����Ϊ�ա�
1. ��������в�Ϊ�յ�ʱ�򣬽���Ӧ�Ķ��м���cp������
2. ���ϴ�cp����ͷ������һ��cp������cp���������timeSlice�����ݻ��߶���Ϊ�ա����������timeSlice������֮�󣬸ö��в�Ϊ�գ�
�ͽ�����ӵ�cp���е�β���������cp�ж��������У�ֻҪ��һ������Ϊ�գ��Ͳ�����cp����cp�����С�
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
	//process unit�Ļ�����
	static mutex mutexOfProcessMap;
};

#endif //CONTINUOUSPROCESSING_EXECUTESCHEDULER_H