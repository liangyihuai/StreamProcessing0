#include "../stdafx.h"
#include "ExecuteScheduler.h"
#include <thread>
#include "../cqindex/ProcessRegisterForCQIndex.h"


priority_queue<Process_TriggerTime*, vector<Process_TriggerTime*> > ExecuteScheduler::cq_pq;

priority_queue<Process_TriggerTime*, vector<Process_TriggerTime*> > ExecuteScheduler::cep_pq;

void ExecuteScheduler::initialize() {
	try {
		std::lock_guard<mutex> lg(ProcessRegister::mutexOfProcessRegister);//mutex lock
		buildGraph();
	}
	catch (std::logic_error& e) {
		std::cout << "[exception caught]\n";
	}
}

void ExecuteScheduler::buildGraph() {
	TopoGraph::setEventFilter(ProcessRegister::eventProcess);//add Event Filter processing
	for (Process* p : ProcessRegister::getAllEventCapture()) {//add Event Capture
		TopoGraph::addProcessUnitToGraph(p);
	}

	for (Process* p : ProcessRegister::getAllCQ()) {//add CQ
		TopoGraph::addProcessUnitToGraph(p);
	}

	for (Process* p: ProcessRegister::getCEPs()) {//add CEP
		TopoGraph::addProcessUnitToGraph(p);
	}
}

void ExecuteScheduler::rebuildGraph() {
	try {
		std::lock_guard<mutex> lg(ProcessRegister::mutexOfProcessRegister);//mutex lock
		TopoGraph::clear();
		for (Process * p : ProcessRegister::allProcess()) {
			p->removeAllDownStreamQueuesAndNames();
		}
		buildGraph();
	}
	catch (std::logic_error& e) {
		std::cout << "[exception caught]\n";
	}
}

void ExecuteScheduler::runProcessQueue(){
	do {
		try {
			std::lock_guard<mutex> lg(ProcessRegister::mutexOfProcessRegister);//mutex lock
			for (auto iter = ProcessRegister::processSet.begin(); iter != ProcessRegister::processSet.end(); iter++){
				(*iter)->process(100);
			}
		}catch (std::logic_error& e) {
			std::cout << "[exception caught]\n";
		}
	} while (true);
}


void ExecuteScheduler::buildTriggerTimePriorityQueue() {
	try {
		std::lock_guard<mutex> lg(ProcessRegister::mutexOfProcessRegister);//mutex lock
		for (auto iter = ProcessRegister::processSet.begin();
			iter != ProcessRegister::processSet.end(); iter++) {
			if (CEPProcess* cep = (CEPProcess*)dynamic_cast<CEPProcess*>(*iter)) {
				if (cep->win != nullptr) {
					Process_TriggerTime* ptt = new Process_TriggerTime(cep, cep->windowList[0]->getWinSliding());
					cep_pq.push(ptt);
				}
			}else if (CQProcess * cq = (CQProcess*)dynamic_cast<CQProcess*>(*iter)) {
				if (cq->windowList.size() > 0) {
					Process_TriggerTime* ptt = new Process_TriggerTime(cq, cq->windowList[0]->getWinSliding());
					cq_pq.push(ptt);
				}
			}
		}
	}
	catch (std::logic_error& e) {
		std::cout << "[exception caught]\n";
	}
}