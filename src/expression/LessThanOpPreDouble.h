//
// Created by USER on 12/6/2018.
//

#ifndef CONTINUOUSPROCESSING_LESSTHANOPPREDOUBLE_H
#define CONTINUOUSPROCESSING_LESSTHANOPPREDOUBLE_H

#include "OperatorPredicate.h"
#include "../op/Operator.h"

class LessThanOpPreDouble: public OperatorPredicate{
private:
    Operator * op;
    double value;
public:

    LessThanOpPreDouble(Operator * o, double value){
        this->op = o;
		this->value = value;
    }

    bool check(EventPtr e){
        ResultPtr result = op->result(e);
        return result->getDouble() < value;
    }
};

#endif //CONTINUOUSPROCESSING_LESSTHANOPPREDOUBLE_H
