#pragma once

#include "Result.h"

class BoolResult : public Result<bool> {
private:
	bool value;
public:
	BoolResult() {}

	BoolResult(bool value) : value(value) {}

	void setValue(int v) {
		this->value = v;
	}

	bool getResult() override{
		return value;
	};
};