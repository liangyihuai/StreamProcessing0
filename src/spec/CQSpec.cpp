#include "../stdafx.h"
#include "CQSpec.h"
#include "../execution/CQProcess.h"

CQProcess * CQSpec::instance() {
	CQProcess* cq = new CQProcess(outputStream);
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
	cq->setInputStreamNames(inputStreams);
	cq->setOutputStreamName(outputStream);
	cq->setPredicate(predicate);
 	return cq;
}

void CQSpec::setInputStreams(vector<string> names) {
	this->inputStreams = names;
}

void CQSpec::setOutputStream(string name) {
	this->outputStream = name;
}

void CQSpec::setPredicate(Predicate * pre) {
	this->predicate = pre;
}

void CQSpec::setWindowlen(int len) {
	this->winLen = len;
}

void CQSpec::setWindowSliding(int sliding) {
	this->winSliding = sliding;
}