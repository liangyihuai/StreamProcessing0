#include "../stdafx.h"
#include "CQSpec.h"
#include "../execution/CQProcess.h"

Predicate* getPredicateByStreamName(vector<Predicate*> predicateList, string streamName) {
	for (Predicate* pre : predicateList) {
		if (pre->streamName == streamName) return pre;
	}
	return nullptr;
}

CQProcess * CQSpec::instance() {
	CQProcess* cq = new CQProcess(inputStreams, outputStream);
	if (winLen > 0) {
		vector<Window*> windowList;
		for (int i = 0; i < inputStreams.size(); i++) {
			NaiveTimeSlidingWindow* nWin = new NaiveTimeSlidingWindow(winLen);
			nWin->setTimeSliding(winSliding);
			windowList.push_back(nWin);
		}
		cq->setWindows(windowList);
	}
	cq->newAttrNames = newAttrNames;
	cq->newAttrValues = newAttrValues;
	cq->operatorNames = operatorNames;
	cq->operatorParamaters = operatorParams;
	cq->setOutputStreamName(outputStream);

	////////////start to set predicate/////////////
	vector<Predicate*> predicatesResult;
	for (string inputStream : inputStreams) {
		Predicate* pre = getPredicateByStreamName(predicateList, inputStream);
		if (pre != nullptr) {
			predicatesResult.push_back(pre);
		}else {
			Predicate* newPre = new TruePredicate();
			newPre->streamName = inputStream;
			predicatesResult.push_back(newPre);
		}
	}
	cq->setPredicates(predicatesResult);
	///////////end to set predicate////////////////

 	return cq;
}

void CQSpec::setInputStreams(vector<string> names) {
	this->inputStreams = names;
}

void CQSpec::setOutputStream(string name) {
	this->outputStream = name;
}

void CQSpec::setPredicates(vector<Predicate*> preList) {
	this->predicateList = preList;
}

void CQSpec::setWindowlen(int len) {
	this->winLen = len;
}

void CQSpec::setWindowSliding(int sliding) {
	this->winSliding = sliding;
}