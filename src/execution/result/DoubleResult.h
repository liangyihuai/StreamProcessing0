//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_DOUBLERESULT_H
#define CONTINUOUSPROCESSING_DOUBLERESULT_H

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

	double getDouble() {
		return value;
	};

};

#endif //CONTINUOUSPROCESSING_DOUBLERESULT_H
