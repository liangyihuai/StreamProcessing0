//
// Created by USER on 12/6/2018.
//
#include "stdafx.h"
#include "ExistOp.h"

ExistOp::ExistOp(string _streamName) {
	this->streamName = _streamName;
}

ResultPtr ExistOp::result(EventPtr event) {
	if (!event)
		return ResultPtr(new BoolResult(false));
	else
		return ResultPtr(new BoolResult(true));
}