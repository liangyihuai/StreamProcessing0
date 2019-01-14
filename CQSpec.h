#pragma once

#include "Spec.h"
#include "Predicate.h"
#include "Window.h"
#include "Utils.h"
#include "CQProcess.h"
#include "CQStoreResultListener.h"

class CQSpec : public Spec{
private:
	string inputStream;
	string outputStream;
	Predicate * predicate;
	string windowType;
	int winLen;
	int winSliding;
public:
	CQProcess * instance() {
		CQProcess* cq = new CQProcess();
		if (windowType.length() > 0) {
			windowType = Utils::toLower(windowType);
			if (windowType == "slidingwindowofcount") {

			}else if (windowType == "slidingwindowoftime") {

			}else if (windowType == "tumblecountwindow") {

			}else if (windowType == "tumbletimewindow") {

			}
		}
		cq->setInputStream(inputStream);
		cq->setOutputStreamName(outputStream);
		cq->setPredicate(predicate);
		cq->setResultListener(new CQStoreResultListener());
		return cq;
	}

	void setInputStream(string name) {
		this->inputStream = name;
	}

	void setOutputStream(string name) {
		this->outputStream = name;
	}

	void setPredicate(Predicate * pre) {
		this->predicate = pre;
	}

	void setWindowType(string type) {
		this->windowType = type;
	}

	void setWindowlen(int len) {
		this->winLen = len;
	}

	void setWindowSliding(int sliding) {
		this->winSliding = sliding;
	}
};