//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_LONGRESULT_H
#define CONTINUOUSPROCESSING_LONGRESULT_H

#include "Result.h"

class LongResult : public Result {
private:
	long value;
public:
	LongResult() {}

	LongResult(long value) : value(value) {}


	void setValue(long v) {
		this->value = v;
	}

	long getLong() {
		return value;
	}
};


#endif //CONTINUOUSPROCESSING_LONGRESULT_H
