#include "../stdafx.h"
#include "ExistOp.h"
#include "../execution/result/BoolResult.h"

ExistOp::ExistOp(string _streamName) {
	this->streamName = _streamName;
}


ResultPtr<bool> ExistOp::result(EventPtr event) {
	cout << "not implemented." << endl;
	throw runtime_error("");
}

ResultPtr<bool> ExistOp::resultMultEvents(list<EventPtr> *eventList, bool isReset) {
	if (eventList == nullptr || eventList->size() == 0) {
		return ResultPtr<bool>(new BoolResult(false));
	}
	else {
		return ResultPtr<bool>(new BoolResult(true));
	}
}




