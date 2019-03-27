//
// Created by USER on 12/5/2018.
//

#include "../stdafx.h"
#include "Average.h"
#include "../execution/win/Window.h"

ResultPtr Average::result(EventPtr event) {
	DoubleResult * result1 = new DoubleResult();
	if (this->window == nullptr) {
		sum += event->getFloat(attrName);
		count++;
		double ave = sum / count;
		result1->setValue(ave);
	}
	else {
		double d = window->aggregateDoubleValue(event, this);
		result1->setValue(d);
	}
	return ResultPtr(result1);
}

ResultPtr Average::resultMultEvents(list<EventPtr> *eventList, bool isReset) {
	double tempSum = 0.0;
	int tempCount = 0;
	if (!isReset) {
		tempSum = this->sum;
		tempCount = this->count;
	}

	for (EventPtr e : *eventList) {
		tempSum += e->getFloat(attrName);
		tempCount++;
	}
	if (!isReset) {
		this->sum = tempSum;
		this->count = tempCount;
	}

	ResultPtr result(new DoubleResult((double)(tempSum / tempCount)));
	return result;
}

StatefulOperator* Average::clone() {
	Average * newSumOp = new Average(this->attrName);
	if (window != nullptr) {
		newSumOp->window = window->clone();
	}
	return newSumOp;
}
