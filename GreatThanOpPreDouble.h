//
// Created by USER on 12/6/2018.
//

#ifndef CONTINUOUSPROCESSING_OPGREATHANDOUBLE_H
#define CONTINUOUSPROCESSING_OPGREATHANDOUBLE_H

#include "OperatorPredicate.h"
#include "Operator.h"
#include "StatefulOperator.h"


class GreatThanOpPreDouble: public OperatorPredicate{
private:
    Operator *op;
    double value;
public:

    GreatThanOpPreDouble(Operator * o, double value){
        this->op = o;
    }

    bool check(EventPtr e){
        ResultPtr result = op->result(e);
        return result->getDouble() > value;
    }

};

#endif //CONTINUOUSPROCESSING_OPGREATHANDOUBLE_H
