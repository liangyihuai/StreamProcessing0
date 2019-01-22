//
// Created by USER on 12/6/2018.
//
#include "stdafx.h"
#include "ExistOp.h"

ExistOp::ExistOp(string _streamName, int _timeWinLen) {
	this->streamName = _streamName;
	window.setTimeLen(_timeWinLen);
}

bool ExistOp::digestEvent(EventPtr e) {
	window.push_back(e);
	return true;
}

ResultPtr ExistOp::result(EventPtr event) {
	window.refresh();

	if (!window.empty()) return ResultPtr(new BoolResult(true));
	else return ResultPtr(new BoolResult(false));
}


