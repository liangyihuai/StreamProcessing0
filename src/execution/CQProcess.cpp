//
// Created by USER on 12/5/2018.
//
#include "../stdafx.h"
#include "CQProcess.h"
#include "../cqindex/ProcessRegisterForCQIndex.h"
#include "../op/win/Window.h"

CQProcess::CQProcess(string outputStreamName) {
	this->inputQueue = new queue<EventPtr>();
	this->outputStreamName = outputStreamName;
}

void CQProcess::addOutputQueue(queue<EventPtr> *outputQueue, string outputStreamNameOfProcess) {
	outputQueueSet.insert(outputQueue);
	connectedOutputNameSet.insert(outputStreamNameOfProcess);
}

bool CQProcess::process(int timeSlice){
	while (!inputQueue->empty() && timeSlice > 0) {
		EventPtr e = inputQueue->front();
		if (predicate->check(e)) {
			if (USE_CQ_INDEX && ProcessRegisterForCQIndex::isIndexed(this)) {
				list<Process*> processList = ProcessRegisterForCQIndex::getIndexByProcess(this)->filter(e);
				CQProcess * cq = nullptr;
				for (Process* p : processList) {
					cq = dynamic_cast<CQProcess*>(p);
					cq->addEventToQueue(e);
				}
			}else {
				for (queue<EventPtr>* q : outputQueueSet) {
					q->push(e);
				}
			}
		}
		timeSlice--;
		inputQueue->pop();
	}
	if (!inputQueue->empty()) {
		return false;
	}
	return true;
}

vector<string> CQProcess::getInputStreamNames() {
	vector<string> result;
	result.push_back(inputStreamName);
	return result;
}

vector<queue<EventPtr>*> CQProcess::getInputQueues() {
	vector<queue<EventPtr>*> result;
	result.push_back(inputQueue);
	return result;
}

string CQProcess::getOutputStreamName() {
	return outputStreamName;
}


void CQProcess::setPredicate(Predicate * pre) {
	this->predicate = pre;
}

void CQProcess::setInputStreamName(string name) {
	this->inputStreamName = name;
}

void CQProcess::setOutputStreamName(string stream){
    this->outputStreamName = stream;
}

queue<EventPtr>* CQProcess::getInputQueue() {
	return this->inputQueue;
}

Predicate* CQProcess::getPredicate() {
	return this->predicate;
}

set<string> CQProcess::getConnectedOutputNameSet() {
	return this->connectedOutputNameSet;
}

void CQProcess::addEventToQueue(EventPtr e) {
	inputQueue->push(e);
}

CQProcess::~CQProcess(){
	delete predicate; predicate = nullptr;
	delete inputQueue; inputQueue = nullptr;
}