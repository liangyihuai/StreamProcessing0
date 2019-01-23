//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_EXECUTESCHEDULER_H
#define CONTINUOUSPROCESSING_EXECUTESCHEDULER_H


#include "DerivedEventStore.h"
#include <unordered_map>
#include "EventProcess.h"
#include "EventCapture.h"
#include "CQProcess.h"
#include "CEPProcess.h"

/*
ά��һ��������в�Ϊ�յ�cp���У�ѭ������cp����������е����ݣ�ֱ��cp����Ϊ�ա�
1. ��������в�Ϊ�յ�ʱ�򣬽���Ӧ�Ķ��м���cp������
2. ���ϴ�cp����ͷ������һ��cp������cp���������timeSlice�����ݻ��߶���Ϊ�ա����������timeSlice������֮�󣬸ö��в�Ϊ�գ�
�ͽ�����ӵ�cp���е�β���������cp�ж��������У�ֻҪ��һ������Ϊ�գ��Ͳ�����cp����cp�����С�
*/
class ExecuteScheduler {
private:
    //system wise id
    // unsigned int id = 0;

	//static EventProcess eventProcess;

 //   //stream name -> eventCapture
 //   static std::list<EventCapture*> eventCaptureList;

 //   //stream name -> CQProcess object
 //   static std::unordered_map<std::string, list<CQProcess*>*> cqMap;

 //   //stream name -> CEPProcess object
	//static std::unordered_map<std::string, list<CEPProcess*>*> cepMap;

	static std::queue<Process*> processQueue;

	static EventProcess eventProcess;

	//output stream name -> process
	static std::unordered_map<string, Process*> processMap;

	//connect process unit A and B. It is used to build compute graph
	static void connectTowProcessUnit(string inputStreamNameOfB, queue<EventPtr> * inputQueueOfB);

	//check whether the outputQueue reference of a process is nullptr.
	static void checkGraph();

public:
	
	static void registerEventProcess(EventProcess e);

    //static void executeEventCapture(EventPtr e);

	/*static void registerEventCapture(EventCapture *);

	static void registerCQProcess(CQProcess* cq);

	static void registerCEPProcess(CEPProcess* cep);*/

	/*static void executeCQProcess();

	static void executeCEPProcess();*/

	static void initialize();

	static void runProcessQueue();

	static void pushBackProcessQueue(Process * cp);

	static void buildGraph();
};

#endif //CONTINUOUSPROCESSING_EXECUTESCHEDULER_H
