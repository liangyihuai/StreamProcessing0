//
// Created by USER on 12/5/2018.
//

#include "stdafx.h"

#include "CEPProcess.h"
#include "DerivedEventStore.h"
#include "TumbleTimeWindow.h"

CEPProcess::CEPProcess(int inputStreamNum, string outputStreamName, queue<EventPtr>* outputQueue) {
	this->outputStreamName = outputStreamName;
	this->outputQueue = outputQueue;

	for (int i = 0; i < MAX_READER; i++) {
		windowVec.push_back(nullptr);
	}
	this->window = new TumbleTimeWindow(1000);

	inputQueues = new vector<queue<EventPtr>*>();
	for (int i = 0; i < inputStreamNum; i++) {
		inputQueues->push_back(new queue<EventPtr>());
	}
}

//tumble time sliding window.
//at every sliding time, call this method.
void CEPProcess::process(int timeSlice){
	//whether it is the time to evaluate again
	if (!window->slidingNow()) return;

	int satifiedStreamCount = 0;//if the stream meets conditions, plus one.
	//for each input stream

	for (int i = 0; i < inputQueues->size(); i++) {
		bool result = false;
		WindowBase * win = nullptr;
		
		unsigned int satisfiedMark = 0;//32 bit, if the bit value is 1, the associated predicate saticfied.
		int satisfiedCount = 0;//if one predicate meets conditions, plus one.
		while (!win->isEmpty()) {//get events from the window
			EventPtr e = win->next();
			vector<Predicate*>* preVec = predicateMatrix[i];
			for (int i = 0; i < preVec->size(); i++) {
				Predicate* pre = (*preVec)[i];//check the predicate
				if (pre->check(e)) {
					if (satisfiedMark ^ (1 << i) == 1) {
						satisfiedMark = satisfiedMark ^ (1 << i);
						satisfiedCount++;
						if (satisfiedCount == preVec->size()) 
							break;
					}
				}
			}
			if (satisfiedCount == preVec->size()) {//all predicates satisfies the conditions
				satifiedStreamCount++;
				while (!win->isEmpty())//skip the rest events in the queue
					win->next();
			}
		}
	}
	if (satifiedStreamCount == inputQueues->size()) {
		if (resultListener) {
			MulStreamResult * result = new MulStreamResult();
			result->addDeriveEventPtr(resultStreams);

			resultListener->update(ResultPtr(result));
		}
	}
}


void CEPProcess::addPredicate(Predicate * pre, string streamName){
	bool exists = false;
    //find a reader according stream name
	for (int i = 0; i < inputQueues->size(); i++) {
        if(inputStreamNames[i] == streamName){
			predicateMatrix[i]->push_back(pre);
			exists = true;
			break;
        }
    }
    if(exists == false){
		LOG(WARNING) << "there is no specified input stream name in this CEP process, name is:" << streamName;
    }
}

void CEPProcess::setResultListener(ResultListener* listener){
    this->resultListener = listener;
}

//
void CEPProcess::setWindow(WindowBase *w){
	if (!w) {
		LOG(ERROR) << "null pointer";
		throw runtime_error("null pointer");
	}
	WindowBase * tempWin = window;
	this->window = w;
	delete tempWin;
	tempWin = nullptr;
}

CEPProcess::~CEPProcess(){
	for (WindowBase * win : windowVec) {
		delete win;
		win = nullptr;
	}

    delete resultListener; resultListener = nullptr;
	delete window;
	for (int i = 0; i < inputQueues->size(); i++) {
		delete (*inputQueues)[i];
		(*inputQueues)[i] = nullptr;
	}
	delete inputQueues;
	inputQueues = nullptr;

	delete outputQueue; outputQueue = nullptr;
}