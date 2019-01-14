//
// Created by USER on 12/5/2018.
//
#include "stdafx.h"
#include "CQProcess.h"
#include "DerivedEventStore.h"

void CQProcess::process(){
	if (!reader) {
		LOG(ERROR) << "the queue reader is nullptr";
		throw runtime_error("");
	}
   
    EventPtr e = nullptr;
    while(!reader->isEmpty()){
        e = reader->dequeue();
		if (predicate->check(e)) {//check condition
			if (resultListener) {
				ResultPtr r(new EnhanceEventResult(e, outputStreamName));
				resultListener->update(r);
			}
		}
    }
}

void CQProcess::setPredicate(Predicate * pre) {
	this->predicate = pre;
}

void CQProcess::setOutputStreamName(string stream){
    this->outputStreamName = stream;
}

void CQProcess::setResultListener(ResultListener* listener){
    this->resultListener = listener;
}

void CQProcess::setInputStream(string s){
    this->reader = new QueueReader();
    reader->setStreamName(s);
	//DerivedEventStore::registerReader(outputStreamName, reader);
}

void CQProcess::setWindow(Window *w){
    this->win = w;
}

QueueReader* CQProcess::getReader(){
    return reader;
}

CQProcess::~CQProcess(){
	delete predicate; predicate = nullptr;
    delete reader; reader = nullptr;
    delete win; win = nullptr;
    delete resultListener; resultListener = nullptr;
}