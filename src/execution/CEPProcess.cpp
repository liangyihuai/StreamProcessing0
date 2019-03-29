#include "../stdafx.h"

#include "CEPProcess.h"
#include "result/MultEventResult.h"
#include "../op/ExistOp.h"
#include "result/ResultListener.h"

mutex CEPProcess::mutexOfCEPResult;

CEPProcess::CEPProcess(vector<string> inputStreamNames, string outputStreamName) {
	this->outputStreamName = outputStreamName;
	this->inputStreamNames = inputStreamNames;
	int inputStreamNum = inputStreamNames.size();
	inputQueues = new vector<queue<EventPtr>*>();
	for (string inputStreamName: inputStreamNames) {
		inputQueues->push_back(new queue<EventPtr>());
		NaiveTimeSlidingWindow<bool> * win = new NaiveTimeSlidingWindow<bool>(windowLen);
		ExistOp* existOp = new ExistOp(inputStreamName);//operator
		win->setStatefulOperator(existOp);
		timeSlidingWinForExistOpVec.push_back(win);//vector
	}
}

bool CEPProcess::process(int timeSlice){
	int nonEmptyCount = 0;
	Window<bool> *input_queue_win = nullptr;

	for (int i = 0; i < inputQueues->size(); i++) {
		int timeSlice_i = timeSlice;
		queue<EventPtr> * q = (*inputQueues)[i];
		while (!q->empty() && timeSlice_i > 0) {
			try {
				std::lock_guard<mutex> lg(CEPProcess::mutexOfCEPResult);//mutex lock
				input_queue_win = timeSlidingWinForExistOpVec[i];
				input_queue_win->push_back(q->front());
			}catch (std::logic_error& e) {
				std::cout << "[exception caught]\n";
			}
			q->pop();
			timeSlice_i--;
		}
		if (!q->empty()) nonEmptyCount++;
	}
	if (nonEmptyCount == inputQueues->size()) 
		return false;
	return true;
}

vector<string> CEPProcess::getInputStreamNames() {
	return inputStreamNames;
}

vector<queue<EventPtr>*> CEPProcess::getInputQueues() {
	return *inputQueues;
}

string CEPProcess::getOutputStreamName() {
	return outputStreamName;
}

void CEPProcess::addOutputQueue(queue<EventPtr>* outputQueue, string outputStreamNameOfProcess) {
	std::cout << "not implemented method addOutputQueue";
	throw runtime_error("");
}

set<string> CEPProcess::getConnectedOutputNameSet() {
	std::cout << "not implemented method addOutputQueue";
	throw runtime_error("");
}

void CEPProcess::result(){
	int satisfiedCount = 0;
	//for each input stream
	for (int i = 0; i < timeSlidingWinForExistOpVec.size(); i++) {
		bool result = false;
		//32 bit, if the bit value is 1, the associated predicate saticfied.
		if (timeSlidingWinForExistOpVec[i] == nullptr) {
			std::cout << "The operator ExistOp is nullptr, index is " << i << ", outputStreamName is " << outputStreamName;
			throw runtime_error("");
		}
		try {
			std::lock_guard<mutex> lg(CEPProcess::mutexOfCEPResult);//mutex lock
			bool resultOfExistOp;
			timeSlidingWinForExistOpVec[i]->reevaluate(resultOfExistOp);
			if (resultOfExistOp) {satisfiedCount++;}
		}catch (std::logic_error& e) {
			std::cout << "[exception caught]\n";
		}
	}
	if (satisfiedCount == timeSlidingWinForExistOpVec.size()) {
		if (resultListener) {
			MultEventResult * result = new MultEventResult();
			result->addDeriveEventPtr(outputStreamName);

			resultListener->update(ResultPtr<EventPtr>(result));
		}
	}
}

void CEPProcess::setInputStreamNames(vector<string> names) {
	this->inputStreamNames = names;
}

void CEPProcess::setResultListener(ResultListener<EventPtr>* listener){
    this->resultListener = listener;
}

CEPProcess::~CEPProcess(){
    delete resultListener; resultListener = nullptr;
	for (int i = 0; i < inputQueues->size(); i++) {
		delete (*inputQueues)[i];
		(*inputQueues)[i] = nullptr;
	}
	delete inputQueues;
	inputQueues = nullptr;

	for (Window<bool>* win : timeSlidingWinForExistOpVec) {
		delete win;
		win = nullptr;
	}
}

