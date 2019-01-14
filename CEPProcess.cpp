//
// Created by USER on 12/5/2018.
//

#include "stdafx.h"

#include "CEPProcess.h"
#include "DerivedEventStore.h"
#include "TumbleTimeWindow.h"

CEPProcess::CEPProcess() {
	for (int i = 0; i < MAX_READER; i++) {
		windowVec.push_back(nullptr);
	}
	this->window = new TumbleTimeWindow(1000);
}

//tumble time sliding window.
//at every sliding time, call this method.
bool CEPProcess::process(){
	//whether it is the time to evaluate again
	if (!window->slidingNow()) return false;

	int satifiedStreamCount = 0;//if the stream meets conditions, plus one.
	//for each input stream
	for (int i = 0; i < readerVec.size(); i++) {
		bool result = false;
		WindowBase * win = nullptr;
		if ((win = windowVec[i]) == nullptr) {//initailize the window
			WindowBase * newWin = window->clone();
			newWin->setReader(readerVec[i]);
			win = newWin;
			windowVec[i] = newWin;
		}
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
	if (satifiedStreamCount == readerVec.size()) {
		if (resultListener) {
			MulStreamResult * result = new MulStreamResult();
			result->addDeriveEventPtr(resultStreams);

			resultListener->update(ResultPtr(result));
		}
	}
    return true;
}


void CEPProcess::addPredicate(Predicate * pre, string stream){
	if (readerVec.size() >= MAX_READER) {
		LOG(ERROR) << "the max reader number is 10, but the current size is "<< readerVec.size();
		throw runtime_error("");
	}

	bool exists = false;
    //find a reader according stream name
	for (int i = 0; i < readerVec.size(); i++) {
		QueueReader* tempReader = readerVec[i];
        if(tempReader->getStreamName() == stream){
			predicateMatrix[i]->push_back(pre);
			exists = true;
			break;
        }
    }
    if(exists == false){
		//create a reader
        QueueReader* reader = new QueueReader();
        reader->setStreamName(stream);
		readerVec.push_back(reader);
		//add predicate
		vector<Predicate*> *preVec = new vector<Predicate*>();
		preVec->push_back(pre);
		predicateMatrix.push_back(preVec);
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

set<QueueReader*> CEPProcess::getReaderSet(){
    set<QueueReader*> s;

	for (QueueReader * reader: readerVec) {
        s.insert(reader);
    }
    return s;
}

void CEPProcess::addOutputStream(string streamName) {
	resultStreams.push_back(streamName);
}

CEPProcess::~CEPProcess(){
	for (WindowBase * win : windowVec) {
		delete win;
		win = nullptr;
	}

	for (QueueReader* reader : readerVec) {
		delete reader;
		reader = nullptr;
	}


	/*for (vector<Predicate*> * vec : predicateMatrix) {
		for (Predicate* pre : *vec) {
			delete pre;
			pre = nullptr;
		}
		delete vec;
		vec = nullptr;
	}*/
    delete resultListener; resultListener = nullptr;
	delete window;
}