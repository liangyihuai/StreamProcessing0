#pragma once


#include "OperatorPredicate.h"
#include "../op/inter/Operator.h"

class LessThanOpPreDouble: public OperatorPredicate{
private:
    Operator<double> * op;
    double value;
public:

    LessThanOpPreDouble(Operator<double> * o, double value){
        this->op = o;
		this->value = value;
    }

    bool check(EventPtr e){
        ResultPtr<double> result = op->result(e);
        return result->getResult() < value;
    }
};

