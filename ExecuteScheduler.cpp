#include "stdafx.h"
#include "ExecuteScheduler.h"
#include <thread>


std::queue<Process*> ExecuteScheduler::processQueue;
std::set<Process*> ExecuteScheduler::processSet;
EventProcess * ExecuteScheduler::eventProcess;
std::unordered_map<string, Process*> ExecuteScheduler::processMap;

set<CEPProcess*> ExecuteScheduler::cepSet;

void ExecuteScheduler::registerEventProcess(EventProcess* ep) {
	ExecuteScheduler::eventProcess = ep;
}

EventProcess* ExecuteScheduler::getEventProcess() {
	return ExecuteScheduler::eventProcess;
}


void ExecuteScheduler::initialize() {
	buildGraph();
}


void ExecuteScheduler::runProcessQueue(){
	//launch a console
	FILE* fp = NULL;
	AllocConsole();
	freopen_s(&fp, "CONOUT$", "w+t", stdout);
	cout << "start stream processing..." << endl;

	do {
		/*while (!processQueue.empty()) {
			Process* p = processQueue.front();
			bool empty = p->process(100);
			processQueue.pop();
			processSet.erase(p);
			if (!empty) {
				pushBackProcessQueue(p);
			}
		}
		Sleep(300);*/

		//遍历所有的Process依次调用process函数
		Process * p = nullptr;
		for (auto iter = processMap.begin(); iter != processMap.end(); iter++) {
			p = iter->second;
			p->process(100);
		}
	} while (true);

	fclose(stdout);
	FreeConsole();
}

void ExecuteScheduler::registerProcess(string outputStreamName, Process *p) {
	processMap[outputStreamName] = p;

	if (CEPProcess * cep = dynamic_cast<CEPProcess*>(p)) {
		addCEP(cep);
	}
}

void ExecuteScheduler::connectTowProcessUnit(string inputStreamNameOfB, queue<EventPtr> * inputQueueOfB) {
	if (eventProcess->getOutputStreamName() == inputStreamNameOfB) {
		eventProcess->addOutputQueue(inputQueueOfB);
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
	if (processSet.find(cp) != processSet.end()) {
		processQueue.push(cp);
		processSet.insert(cp);
	}
}

void ExecuteScheduler::addCEP(CEPProcess * p) {
	cepSet.insert(p);
}

set<CEPProcess*> ExecuteScheduler::getCEPs() {
	return cepSet;
}

