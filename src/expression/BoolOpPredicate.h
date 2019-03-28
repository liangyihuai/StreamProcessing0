#pragma once

#include "OperatorPredicate.h"
#include "../op/inter/Operator.h"

class BoolOpPredicate: public OperatorPredicate{
private:
	Operator<bool> * op;
public:

	BoolOpPredicate(Operator<bool> * o) {
		this->op = o;
	}

	bool check(EventPtr e) {
		ResultPtr<bool> result = op->result(e);
		return result->getResult();
	}
};