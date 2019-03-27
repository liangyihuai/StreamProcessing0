//
// Created by USER on 12/5/2018.
//
#include "../stdafx.h"
#include "Max.h"


ResultPtr Max::result(EventPtr event) {
	DoubleResult * result1 = new DoubleResult;
	if (window == nullptr) {
		if (max < event->getFloat(attr)) {
			max = event->getFloat(attr);
		}
		result1->setValue(max);
	}
	else {
		double d = window->aggregateDoubleValue(event, this);
		result1->setValue(max);
	}
	return ResultPtr(result1);
}

ResultPtr Max::resultMultEvents(list<EventPtr> *eventList, bool isReset) {
	float tempMax = -99999;
	float t = 0.0f;
	for (EventPtr e : *eventList) {
		t = e->getFloat(attr);
		if (tempMax < t) tempMax = t;
	}
	if (!isReset) {
		if (max < tempMax) {
			max = tempMax;
		}
		else {
			tempMax = max;
		}
	}
	ResultPtr result(new DoubleResult(tempMax));
	return result;
}

StatefulOperator* Max::clone() {
	Max * newSumOp = new Max(attr);
	if (window != nullptr)
		newSumOp->window = window->clone();
	return newSumOp;
}