#include "stdafx.h"
#include "ExecuteScheduler.h"
#include <thread>
#include "ProcessRegisterForCQIndex.h"


std::queue<Process*> ExecuteScheduler::processQueue;
std::set<Process*> ExecuteScheduler::processSet;
EventProcess * ExecuteScheduler::eventProcess;
std::unordered_map<string, Process*> ExecuteScheduler::processMap;

set<CEPProcess*> ExecuteScheduler::cepSet;

mutex ExecuteScheduler::mutexOfProcessMap;

void ExecuteScheduler::registerEventProcess(EventProcess* ep) {
	ExecuteScheduler::eventProcess = ep;
}

EventProcess* ExecuteScheduler::getEventProcess() {
	return ExecuteScheduler::eventProcess;
}


void ExecuteScheduler::initialize() {
	try {
		std::lock_guard<mutex> lg(ExecuteScheduler::mutexOfProcessMap);//mutex lock

		buildGraph();
	}
	catch (std::logic_error& e) {
		std::cout << "[exception caught]\n";
	}
}


void ExecuteScheduler::runProcessQueue(){
	//launch a console
	/*FILE* fp = NULL;
	AllocConsole();
	freopen_s(&fp, "CONOUT$", "w+t", stdout);
	cout << "start stream processing..." << endl;*/

	Process * p = nullptr;
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

		try {
			std::lock_guard<mutex> lg(ExecuteScheduler::mutexOfProcessMap);//mutex lock
			//遍历所有的Process依次调用process函数
			for (auto iter = processMap.begin(); iter != processMap.end(); iter++) {
				p = iter->second;
				p->process(100);
			}
		}
		catch (std::logic_error& e) {
			std::cout << "[exception caught]\n";
		}
		
	} while (true);

	/*fclose(stdout);
	FreeConsole();*/
}

void ExecuteScheduler::registerProcess(string outputStreamName, Process *p) {
	processMap[outputStreamName] = p;

	if (CEPProcess * cep = dynamic_cast<CEPProcess*>(p)) {
		addCEP(cep);
	}

	//add the Process Unit to the processing graph
	addProcessUnitToGraph(p);
}


void ExecuteScheduler::buildGraph() {
	for (auto iter = processMap.begin(); iter != processMap.end(); iter++) {//iterate processes
		Process * pro = iter->second;
		addProcessUnitToGraph(pro);
	}

	if (USE_CQ_INDEX) {
		ProcessRegisterForCQIndex::buildIndexGraph(processMap, MAX_CONNECTION_FOR_INDEX, 7);
	}
}

void ExecuteScheduler::updateGraph() {
	buildGraph();
}

void ExecuteScheduler::addProcessUnitToGraph(Process* processOfB) {
	vector<string> inputStreamNames = processOfB->getInputStreamNames();
	for (int i = 0; i < inputStreamNames.size(); i++) {
		vector<queue<EventPtr>*> queues = processOfB->getInputQueues();
		addProcessUnitToGraph(inputStreamNames[i], queues[i], processOfB->getOutputStreamName());
	}
}

void ExecuteScheduler::addProcessUnitToGraph(string inputStreamNameOfB, 
					queue<EventPtr> * inputQueueOfB, string outputNameOfB) {
	if (eventProcess->getOutputStreamName() == inputStreamNameOfB) {
		eventProcess->addOutputQueue(inputQueueOfB);
	}else {
		for (auto iter = processMap.begin(); iter != processMap.end(); iter++) {
			Process * pro = iter->second;
			string inputStreamNameOfA = pro->getOutputStreamName();
			if (inputStreamNameOfA == inputStreamNameOfB) {
				pro->addOutputQueue(inputQueueOfB, outputNameOfB);
			}
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

bool ExecuteScheduler::deleteProcess(string outputStreamName) {
	try {
		std::lock_guard<mutex> lg(ExecuteScheduler::mutexOfProcessMap);//mutex lock
		
		if (processMap.find(outputStreamName) != processMap.end()) {
			Process* process = processMap[outputStreamName];
			processMap.erase(outputStreamName);//delete from processMap
			if (CEPProcess* cep = dynamic_cast<CEPProcess*>(process)) {
				cepSet.erase(cep);//delete CEP from cepSet
			}
			delete process;
			return true;
		}
	}catch (std::logic_error& e) {
		std::cout << "[exception caught]\n";
	}
	return false;
}


Process * ExecuteScheduler::getProcess(string outputStreamName) {
	try {
		std::lock_guard<mutex> lg(ExecuteScheduler::mutexOfProcessMap);//mutex lock

		if (processMap.find(outputStreamName) != processMap.end()) {
			return processMap[outputStreamName];
		}
	}catch (std::logic_error& e) {
		std::cout << "[exception caught]\n";
	}
	return nullptr;
}
