#pragma once

#include "Result.h"

class DoubleResult : public Result<double> {
private:
	double value;
public:
	DoubleResult() {}

	DoubleResult(double value) : value(value) {}

	void setValue(double v) {
		this->value = v;
	}

	double getResult()override {
		return value;
	};

};
