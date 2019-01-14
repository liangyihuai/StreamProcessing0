//
// Created by USER on 12/5/2018.
//
#include "stdafx.h"
#include "Sum.h"

ResultPtr Sum::result(EventPtr event) {
	DoubleResult * result1 = new DoubleResult();
	if (this->window == nullptr) {
		sum += event->getFloat(attrName);
		result1->setValue(sum);
	}
	else {
		double d = window->aggregateDoubleValue(event, this);
		result1->setValue(d);
	}
	return ResultPtr(result1);
}


ResultPtr Sum::resultMultEvents(list<EventPtr> *eventList, bool isReset) {
	double tempSum = 0.0;
	if (!isReset) tempSum = this->sum;

	for (EventPtr e : *eventList) {
		tempSum += e->getFloat(attrName);
	}
	if (!isReset) this->sum = tempSum;

	ResultPtr result(new DoubleResult(tempSum));
	return result;
}

StatefulOperator* Sum::clone() {
	Sum * newSumOp = new Sum(this->attrName);
	if (window != nullptr) {
		newSumOp->window = window->clone();
	}
	return newSumOp;
}