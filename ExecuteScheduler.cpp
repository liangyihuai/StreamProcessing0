//
// Created by USER on 12/5/2018.
//
#include "stdafx.h"
#include "ExecuteScheduler.h"

EventProcess ExecuteScheduler::eventProcess;

//stream name -> eventCapture
std::list<EventCapture*> ExecuteScheduler::eventCaptureList;

//stream name -> CQProcess object
std::unordered_map<std::string, list<CQProcess*>*> ExecuteScheduler::cqMap;

//stream name -> CEPProcess object
std::unordered_map<std::string, list<CEPProcess*>*> ExecuteScheduler::cepMap;

void ExecuteScheduler::registerEventProcess(EventProcess ep) {
	ExecuteScheduler::eventProcess = ep;
}

void ExecuteScheduler::registerEventCapture(EventCapture * ec) {
	if (!ec) {
		LOG(ERROR) << "the input parameter is nullptr";
		throw runtime_error("");
	}

	ExecuteScheduler::eventCaptureList.push_back(ec);
}

void ExecuteScheduler::registerCQProcess(CQProcess* cq){
    QueueReader* reader = cq->getReader();
    string stream = reader->getStreamName();
    if(cqMap.find(stream) == cqMap.end()){
        cqMap[stream] = new list<CQProcess*>;
    }
    list<CQProcess*> * cqList = cqMap[stream];
    cqList->push_back(cq);

    //regester a data reader
    DerivedEventStore::registerReader(stream, reader);
}

void ExecuteScheduler::registerCEPProcess(CEPProcess* cep){
    set<QueueReader*> readerSet = cep->getReaderSet();
    for(QueueReader* reader: readerSet){
        string stream = reader->getStreamName();
        if(cepMap.find(stream) == cepMap.end()){
            cepMap[stream] = new list<CEPProcess*>;
        }
        list<CEPProcess*> * cepList = cepMap[stream];
        cepList->push_back(cep);

        //regester a data reader
        DerivedEventStore::registerReader(stream, reader);
    }
}

void ExecuteScheduler::executeEventCapture(EventPtr e) {
	for (EventCapture * ec : ExecuteScheduler::eventCaptureList) {
		ec->process(e);
	}
}

void ExecuteScheduler::executeCQProcess(){
    //get unempty stream name
    for(string stream: DerivedEventStore::unemptyStreams){
        if(cqMap.find(stream) != cqMap.end()) {
            list<CQProcess*> * processList = cqMap[stream];
            for(CQProcess* process: *processList){
                process->process();
            }
        }
    }
}

void ExecuteScheduler::executeCEPProcess(){
    for(string stream: DerivedEventStore::unemptyStreams){//unemptyStreams have no reduction, need to modify
        if(cepMap.find(stream) != cepMap.end()){
            list<CEPProcess*> * processList = cepMap[stream];
			//traverse all CEPprocess of this stream, need to modify
            for(CEPProcess* process: *processList){
				process->process();
            }
        }
    }
}

void ExecuteScheduler::run(EventPtr incomingEvent) {
	if (ExecuteScheduler::eventProcess.filter(incomingEvent)) {
		/*cout << "id=" << incomingEvent->getId() 
			<< ", iff=" << incomingEvent->getString("iff") 
			<< ", speed=" << incomingEvent->getFloat("speed") 
			<< ", lon=" << incomingEvent->getFloat("lon") 
			<< ",lat=" << incomingEvent->getFloat("lat") << endl;*/
		ExecuteScheduler::executeEventCapture(incomingEvent);
		ExecuteScheduler::executeCQProcess();
		//ExecuteScheduler::executeCEPProcess();
	}
}