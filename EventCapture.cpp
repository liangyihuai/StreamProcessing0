#include "stdafx.h"
#include "EventCapture.h"
#include "ProcessRegisterForCQIndex.h"

EventCapture::EventCapture(string _outputStreamName) {
	inputQueue = new queue<EventPtr>();
	this->outputStreamName = _outputStreamName;
}

vector<string> EventCapture::getInputStreamNames() {
	vector<string> result;
	result.push_back(inputStreamName);
	return result;
}

vector<queue<EventPtr>*> EventCapture::getInputQueues() {
	vector<queue<EventPtr>*> result;
	result.push_back(inputQueue);
	return result;
}

string EventCapture::getOutputStreamName() {
	return outputStreamName;
}

void EventCapture::addOutputQueue(queue<EventPtr> * outputQueue, string outputStreamNameOfProcess) {
	outputQueueSet.insert(outputQueue);
	connectedOutputNameSet.insert(outputStreamNameOfProcess);
}

EventCapture::~EventCapture() {
	while (inputQueue != nullptr && !inputQueue->empty()) {
		inputQueue->pop();
	}
	delete inputQueue; 
	inputQueue = nullptr;
	//delete outputQueue;
}

bool EventCapture::process(int timeSlice) {
	EventPtr e = nullptr;
	while (!inputQueue->empty() && timeSlice > 0) {
		try {
			lock_guard<mutex> lg(EventProcess::mutexOfEventFiler);
			e = inputQueue->front();
			inputQueue->pop();
		}catch (std::logic_error& e) {
			std::cout << "[exception caught]\n";
		}
		if (condition.check(e)) {
			//use CQ index
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
	}
	if (!inputQueue->empty()) return false;
	return true;
}

queue<EventPtr>* EventCapture::getInputQueue() {
	return this->inputQueue;
}

void EventCapture::setCondition(Condition condition) {
	this->condition = condition;
}

void EventCapture::setInputStreamName(string name) {
	this->inputStreamName = name;
}

void EventCapture::setOutputStreamName(string name) {
	this->outputStreamName = name;
}

set<string> EventCapture::getConnectedOutputNameSet() {
	return this->connectedOutputNameSet;
}
