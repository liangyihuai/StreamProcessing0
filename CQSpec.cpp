#include "stdafx.h"
#include "CQSpec.h"

CQProcess * CQSpec::instance() {
	CQProcess* cq = new CQProcess(outputStream);
	if (windowType.length() > 0) {
		windowType = Utils::toLower(windowType);
		if (windowType == "slidingwindowofcount") {

		}
		else if (windowType == "slidingwindowoftime") {

		}
		else if (windowType == "tumblecountwindow") {

		}
		else if (windowType == "tumbletimewindow") {

		}
	}
	cq->setInputStreamName(inputStream);
	cq->setOutputStreamName(outputStream);
	cq->setPredicate(predicate);
	//cq->setResultListener(new CQStoreResultListener());
	return cq;
}

void CQSpec::setInputStream(string name) {
	this->inputStream = name;
}

void CQSpec::setOutputStream(string name) {
	this->outputStream = name;
}

void CQSpec::setPredicate(Predicate * pre) {
	this->predicate = pre;
}

void CQSpec::setWindowType(string type) {
	this->windowType = type;
}

void CQSpec::setWindowlen(int len) {
	this->winLen = len;
}

void CQSpec::setWindowSliding(int sliding) {
	this->winSliding = sliding;
}