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
	EventCapture * instance();

	void setInputStream(string name);

	void setOutputStream(string name);

	void setCondition(Condition con);
};