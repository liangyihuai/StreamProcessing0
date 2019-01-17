//
// Created by USER on 12/4/2018.
//
#include "stdafx.h"
#include "EventCapture.h"

EventCapture::EventCapture(queue<EventPtr> * outputQueue) {
	inputQueue = new queue<EventPtr>();
	this->outputQueue = outputQueue;
}

EventCapture::~EventCapture() {
	delete inputQueue;
	//delete outputQueue;
}

void EventCapture::process(int timeSlice) {
	while (!inputQueue->empty() && timeSlice > 0) {
		EventPtr e = inputQueue->front();
		if (condition.check(e)) {
			outputQueue->push(e);
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