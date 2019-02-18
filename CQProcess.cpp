//
// Created by USER on 12/5/2018.
//
#include "stdafx.h"
#include "CQProcess.h"
#include "DerivedEventStore.h"

CQProcess::CQProcess(string outputStreamName) {
	this->inputQueue = new queue<EventPtr>();
	this->outputStreamName = outputStreamName;
}

void CQProcess::addOutputQueue(queue<EventPtr> *outputQueue) {
	outputQueueSet.insert(outputQueue);
}

bool CQProcess::process(int timeSlice){
	while (!inputQueue->empty() && timeSlice > 0) {
		EventPtr e = inputQueue->front();
		if (predicate->check(e)) {
			for (queue<EventPtr>* q : outputQueueSet) {
				q->push(e);
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

void CQProcess::setWindow(Window *w){
    this->win = w;
}

Predicate* CQProcess::getPredicate() {
	return this->predicate;
}

CQProcess::~CQProcess(){
	delete predicate; predicate = nullptr;
    delete win; win = nullptr;
	delete inputQueue; inputQueue = nullptr;
}