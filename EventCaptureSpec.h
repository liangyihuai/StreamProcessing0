#pragma once

#include "Spec.h"
#include "Condition.h"
#include "EventCapture.h"

class EventCaptureSpec : public Spec {
private:
	string inputStream;
	string outputStream;
	Condition conditon;
public:
	EventCapture * instance() {
		EventCapture * ec = new EventCapture();
		ec->setCondition(conditon);
		ec->setInputStream(inputStream);
		ec->setOutputStream(outputStream);
		return ec;
	}

	void setInputStream(string name) {
		this->inputStream = name;
	}

	void setOutputStream(string name) {
		this->outputStream = name;
	}

	void setCondition(Condition con) {
		this->conditon = con;
	}
};