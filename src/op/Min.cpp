//
// Created by USER on 12/5/2018.
//
#include "../stdafx.h"
#include "Min.h"

ResultPtr Min::result(EventPtr event) {
	DoubleResult * result1 = new DoubleResult;
	if (window == nullptr) {
		if (min > event->getFloat(attr)) {
			min = event->getFloat(attr);
		}
		result1->setValue(min);
	}
	else {
		double d = window->aggregateDoubleValue(event, this);
		result1->setValue(d);
	}
	return ResultPtr(result1);
}

ResultPtr Min::resultMultEvents(list<EventPtr> *eventList, bool isReset) {
	float tempMin = 99999;
	float t = 0.0f;
	for (EventPtr e : *eventList) {
		t = e->getFloat(attr);
		if (tempMin > t) tempMin = t;
	}
	if (!isReset) {
		if (min > tempMin) {
			min = tempMin;
		}
		else {
			tempMin = min;
		}
	}
	ResultPtr result(new DoubleResult(tempMin));
	return result;
}

StatefulOperator* Min::clone() {
	Min * newSumOp = new Min(attr);
	if (window != nullptr)
		newSumOp->window = window->clone();
	return newSumOp;
}
