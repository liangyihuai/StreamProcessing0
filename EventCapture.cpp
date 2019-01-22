#include "stdafx.h"
#include "EventCapture.h"

EventCapture::EventCapture(string _outputStreamName) {
	inputQueue = new queue<EventPtr>();
	this->outputStreamName = _outputStreamName;
}

void EventCapture::addOutputQueue(queue<EventPtr> * outputQueue) {
	outputQueueSet.insert(outputQueue);
}

EventCapture::~EventCapture() {
	delete inputQueue;
	//delete outputQueue;
}

void EventCapture::process(int timeSlice) {
	while (!inputQueue->empty() && timeSlice > 0) {
		EventPtr e = inputQueue->front();
		if (condition.check(e)) {
			for (queue<EventPtr>* q : outputQueueSet) {
				q->push(e);
			}
		}
		inputQueue->pop();
		timeSlice--;
	}
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