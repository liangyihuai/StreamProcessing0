#include "stdafx.h"
#include "ExecuteScheduler.h"
#include <thread>

EventProcess ExecuteScheduler::eventProcess;

////stream name -> eventCapture
//std::list<EventCapture*> ExecuteScheduler::eventCaptureList;
//
////stream name -> CQProcess object
//std::unordered_map<std::string, list<CQProcess*>*> ExecuteScheduler::cqMap;
//
////stream name -> CEPProcess object
//std::unordered_map<std::string, list<CEPProcess*>*> ExecuteScheduler::cepMap;

void ExecuteScheduler::registerEventProcess(EventProcess ep) {
	ExecuteScheduler::eventProcess = ep;
}

//void ExecuteScheduler::registerEventCapture(EventCapture * ec) {
//	if (!ec) {
//		LOG(ERROR) << "the input parameter is nullptr";
//		throw runtime_error("");
//	}
//
//	ExecuteScheduler::eventCaptureList.push_back(ec);
//}
//
//void ExecuteScheduler::registerCQProcess(CQProcess* cq){
//    QueueReader* reader = cq->getReader();
//    string stream = reader->getStreamName();
//    if(cqMap.find(stream) == cqMap.end()){
//        cqMap[stream] = new list<CQProcess*>;
//    }
//    list<CQProcess*> * cqList = cqMap[stream];
//    cqList->push_back(cq);
//
//    //regester a data reader
//    DerivedEventStore::registerReader(stream, reader);
//}
//
//void ExecuteScheduler::registerCEPProcess(CEPProcess* cep){
//    set<QueueReader*> readerSet = cep->getReaderSet();
//    for(QueueReader* reader: readerSet){
//        string stream = reader->getStreamName();
//        if(cepMap.find(stream) == cepMap.end()){
//            cepMap[stream] = new list<CEPProcess*>;
//        }
//        list<CEPProcess*> * cepList = cepMap[stream];
//        cepList->push_back(cep);
//
//        //regester a data reader
//        DerivedEventStore::registerReader(stream, reader);
//    }
//}

//void ExecuteScheduler::executeEventCapture(EventPtr e) {
//	for (EventCapture * ec : ExecuteScheduler::eventCaptureList) {
//		ec->process(e);
//	}
//}

//void ExecuteScheduler::executeCQProcess(){
//    //get unempty stream name
//    for(string stream: DerivedEventStore::unemptyStreams){
//        if(cqMap.find(stream) != cqMap.end()) {
//            list<CQProcess*> * processList = cqMap[stream];
//            for(CQProcess* process: *processList){
//                process->process();
//            }
//        }
//    }
//}

//void ExecuteScheduler::executeCEPProcess(){
//    for(string stream: DerivedEventStore::unemptyStreams){//unemptyStreams have no reduction, need to modify
//        if(cepMap.find(stream) != cepMap.end()){
//            list<CEPProcess*> * processList = cepMap[stream];
//			//traverse all CEPprocess of this stream, need to modify
//            for(CEPProcess* process: *processList){
//				process->process();
//            }
//        }
//    }
//}

void ExecuteScheduler::initialize() {
	buildGraph();

	std::thread th = std::thread(&ExecuteScheduler::runProcessQueue, nullptr);
	th.detach();
}

void ExecuteScheduler::runProcessQueue(){
	do {
		while (!processQueue.empty()) {
			Process* p = processQueue.front();
			bool pushBackToqueue = p->process(100);
			if (pushBackToqueue) processQueue.push(p);
		}
		Sleep(300);
	} while (true);
}

void ExecuteScheduler::connectTowProcessUnit(string inputStreamNameOfB, queue<EventPtr> * inputQueueOfB) {
	if (eventProcess.getOutputStreamName() == inputStreamNameOfB) {
		eventProcess.addOutputQueue(inputQueueOfB);
	}else{
		for (auto iter = processMap.begin(); iter != processMap.end(); iter++) {
			Process * pro = iter->second;
			string inputStreamNameOfA = pro->getOutputStreamName();
			if (inputStreamNameOfA == inputStreamNameOfB) {
				pro->addOutputQueue(inputQueueOfB);
			}
		}
	}
}

void ExecuteScheduler::buildGraph() {
	for (auto iter = processMap.begin(); iter != processMap.end(); iter++) {//iterate processes
		Process * pro = iter->second;
		vector<string> inputNames = pro->getInputStreamNames();
		for (int i = 0; i < inputNames.size(); i++) {//iterate input names
			string inputStreamName = inputNames[i];
			vector<queue<EventPtr>*> inputQueue = pro->getInputQueues();
			connectTowProcessUnit(inputStreamName, (inputQueue)[i]);
		}
	}
}

void ExecuteScheduler::pushBackProcessQueue(Process * cp) {
	processQueue.push(cp);
}




