//
// Created by USER on 12/6/2018.
//

#ifndef CONTINUOUSPROCESSING_OPGREATHANDOUBLE_H
#define CONTINUOUSPROCESSING_OPGREATHANDOUBLE_H

#include "OperatorPredicate.h"
#include "../op/inter/Operator.h"
#include "../op/inter/StatefulOperator.h"


class GreatThanOpPreDouble: public OperatorPredicate{
private:
    Operator<double> *op;
    double value;
public:

    GreatThanOpPreDouble(Operator<double> * o, double value){
        this->op = o;
    }

    bool check(EventPtr e){
        ResultPtr<double> result = op->result(e);
        return result->getResult() > value;
    }

};

#endif //CONTINUOUSPROCESSING_OPGREATHANDOUBLE_H
