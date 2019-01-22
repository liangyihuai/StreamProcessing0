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
			for (queue<EventPtr>* q : *outputQueueSet) {
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

CQProcess::~CQProcess(){
	delete predicate; predicate = nullptr;
    delete win; win = nullptr;
	delete inputQueue; inputQueue = nullptr;
}