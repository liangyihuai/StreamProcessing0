#include "../stdafx.h"
#include "ExecuteScheduler.h"
#include <thread>
#include "../cqindex/ProcessRegisterForCQIndex.h"


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
			for (auto iter = ProcessRegister::processSet.begin(); 
				iter != ProcessRegister::processSet.end(); 
				iter++){
				(*iter)->process(100);
			}
		}catch (std::logic_error& e) {
			std::cout << "[exception caught]\n";
		}
	} while (true);
}
