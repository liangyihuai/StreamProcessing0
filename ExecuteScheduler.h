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

class ExecuteScheduler {
private:
    //system wise id
   // unsigned int id = 0;

	static EventProcess eventProcess;

    //stream name -> eventCapture
    static std::list<EventCapture*> eventCaptureList;

    //stream name -> CQProcess object
    static std::unordered_map<std::string, list<CQProcess*>*> cqMap;

    //stream name -> CEPProcess object
	static std::unordered_map<std::string, list<CEPProcess*>*> cepMap;

public:
	
	static void registerEventProcess(EventProcess );

    static void executeEventCapture(EventPtr e);

	static void registerEventCapture(EventCapture *);

	static void registerCQProcess(CQProcess* cq);

	static void registerCEPProcess(CEPProcess* cep);

	static void executeCQProcess();

	static void executeCEPProcess();

	static void run(EventPtr);

};

#endif //CONTINUOUSPROCESSING_EXECUTESCHEDULER_H
