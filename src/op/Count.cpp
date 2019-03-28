//
// Created by USER on 12/5/2018.
//
#include "../stdafx.h"
#include "Count.h"
#include "../execution/result/LongResult.h"

ResultPtr<long> Count::result(EventPtr event) {
	cout << "not implement function 'result' of class Count" << endl;
	throw runtime_error("");
}

ResultPtr<long> Count::resultMultEvents(list<EventPtr> *eventList, bool isReset) {
	if (!isReset) {
		this->count += eventList->size();
	}else {
		this->count = eventList->size();
	}
	return ResultPtr<long>(new LongResult(count));
}

