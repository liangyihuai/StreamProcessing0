#pragma once

#include "Result.h"

class DoubleResult : public Result {
private:
	double value;
public:
	DoubleResult() {}

	DoubleResult(double value) : value(value) {}

	void setValue(double v) {
		this->value = v;
	}

	double getResultDouble()override {
		return value;
	};

};
