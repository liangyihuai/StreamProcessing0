//
// Created by USER on 12/6/2018.
//
#include "../stdafx.h"
#include "ExistOp.h"

ExistOp::ExistOp(string _streamName, int _timeWinLen) {
	this->streamName = _streamName;
	window.setTimeLen(_timeWinLen);
}

bool ExistOp::digestEvent(EventPtr e) {
	window.push_back(e);
	return true;
}

ResultPtr<bool> ExistOp::result(EventPtr event) {
	ResultPtr<bool> result;
	if (!window.empty()) 
		result = ResultPtr<bool>(new BoolResult(true));
	else
		result = ResultPtr<bool>(new BoolResult(false));

	window.refresh();
	return result;
}


