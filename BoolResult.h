#pragma once

#include "Result.h"

class BoolResult : public Result {
private:
	int value;
public:
	BoolResult() {}

	BoolResult(int value) : value(value) {}

	void setValue(int v) {
		this->value = v;
	}

	bool getBool() {
		if (value) return true;
		return false;
	};

};