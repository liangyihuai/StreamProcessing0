#pragma once

#include "Result.h"

class LongResult : public Result<long> {
private:
	long value;
public:
	LongResult() {}

	LongResult(long value) : value(value) {}

	void setValue(long v) {
		this->value = v;
	}

	long getResult() override {
		return value;
	}
};

