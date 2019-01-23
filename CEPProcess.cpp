#include "stdafx.h"

#include "CEPProcess.h"
#include "DerivedEventStore.h"

CEPProcess::CEPProcess(int inputStreamNum, string outputStreamName) {
	this->outputStreamName = outputStreamName;

	inputQueues = new vector<queue<EventPtr>*>();
	for (int i = 0; i < inputStreamNum; i++) {
		inputQueues->push_back(new queue<EventPtr>());
		existOpVec.push_back(nullptr);//for initializing the capacity of the vector
	}
}

bool CEPProcess::process(int timeSlice){
	for (int i = 0; i < inputQueues->size(); i++) {
		int timeSlice_i = timeSlice;
		queue<EventPtr> * q = (*inputQueues)[i];
		while (!q->empty() && timeSlice_i > 0) {
			existOpVec[i]->digestEvent(q->front());
			q->pop();
			timeSlice_i--;
		}
	}
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

void CEPProcess::addOutputQueue(queue<EventPtr>* outputQueue) {
	LOG(ERROR) << "not implemented method addOutputQueue";
	throw runtime_error("");
}

void CEPProcess::result(){
	int satisfiedCount = 0;
	//for each input stream
	for (int i = 0; i < existOpVec.size(); i++) {
		bool result = false;
		//32 bit, if the bit value is 1, the associated predicate saticfied.
		if (existOpVec[i] == nullptr) {
			LOG(ERROR) << "The operator ExistOp is nullptr, index is " << i << ", outputStreamName is " << outputStreamName;
			throw runtime_error("");
		}
		bool resultOfExistOp = existOpVec[i]->result(nullptr)->getBool();
		if (resultOfExistOp) {
			satisfiedCount++;
		}
	}
	if (satisfiedCount == existOpVec.size()) {
		if (resultListener) {
			MulStreamResult * result = new MulStreamResult();
			result->addDeriveEventPtr(outputStreamName);

			resultListener->update(ResultPtr(result));
		}
	}
}

void CEPProcess::addCondition(ExistOp * con, string inputStreamName) {
	bool exists = false;
    //find a reader according stream name
	for (int i = 0; i < inputQueues->size(); i++) {
        if(inputStreamNames[i] == inputStreamName){
			existOpVec[i] = con;
			exists = true;
			break;
        }
    }
    if(exists == false){
		LOG(WARNING) << "there is no specified input stream name in this CEP process, name is:" << outputStreamName;
    }
}

void CEPProcess::setInputStreamNames(vector<string> names) {
	this->inputStreamNames = names;
}

void CEPProcess::setResultListener(ResultListener* listener){
    this->resultListener = listener;
}

//
void CEPProcess::setWindow(int timeWindowLen){
	this->windowLen = timeWindowLen;
}

CEPProcess::~CEPProcess(){
    delete resultListener; resultListener = nullptr;
	for (int i = 0; i < inputQueues->size(); i++) {
		delete (*inputQueues)[i];
		(*inputQueues)[i] = nullptr;
	}
	delete inputQueues;
	inputQueues = nullptr;

	//delete outputQueue; outputQueue = nullptr;
	for (ExistOp* con : existOpVec) {
		delete con; con = nullptr;
	}
}