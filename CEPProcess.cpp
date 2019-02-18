#include "stdafx.h"

#include "CEPProcess.h"
#include "DerivedEventStore.h"

mutex CEPProcess::mutexOfCEPResult;

CEPProcess::CEPProcess(vector<string> inputStreamNames, string outputStreamName) {
	this->outputStreamName = outputStreamName;
	int inputStreamNum = inputStreamNames.size();
	inputQueues = new vector<queue<EventPtr>*>();
	for (int i = 0; i < inputStreamNum; i++) {
		inputQueues->push_back(new queue<EventPtr>());
		existOpVec.push_back(nullptr);//for initializing the capacity of the vector
	}
	this->inputStreamNames = inputStreamNames;
}

bool CEPProcess::process(int timeSlice){
	int nonEmptyCount = 0;

	for (int i = 0; i < inputQueues->size(); i++) {
		int timeSlice_i = timeSlice;
		queue<EventPtr> * q = (*inputQueues)[i];
		while (!q->empty() && timeSlice_i > 0) {
			//debug
			long long t = q->front()->getTime();

			try {
				std::lock_guard<mutex> lg(CEPProcess::mutexOfCEPResult);//mutex lock
				existOpVec[i]->digestEvent(q->front());
			}catch (std::logic_error& e) {
				std::cout << "[exception caught]\n";
			}

			existOpVec[i]->digestEvent(q->front());
			q->pop();
			timeSlice_i--;
		}
		if (!q->empty()) nonEmptyCount++;
	}
	if (nonEmptyCount == inputQueues->size()) return false;
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
	LOG(ERROR) << "not implemented method addOutputQueue";
	throw runtime_error("");
}

set<string> CEPProcess::getConnectedOutputNameSet() {
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
		try {
			std::lock_guard<mutex> lg(CEPProcess::mutexOfCEPResult);//mutex lock
			bool resultOfExistOp = existOpVec[i]->result(nullptr)->getBool();
			if (resultOfExistOp) {satisfiedCount++;}
		}catch (std::logic_error& e) {
			std::cout << "[exception caught]\n";
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
		if (inputStreamNames.size() == 0) {
			LOG(ERROR) << "the size of inputStreamNames is equal to 0";
			throw runtime_error("");
		}
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
		delete con;
		con = nullptr;
	}
}