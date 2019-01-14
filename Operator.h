//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_OPERATOR_H
#define CONTINUOUSPROCESSING_OPERATOR_H

#include "Result.h"

class Operator {
public:
    virtual ResultPtr result(EventPtr event) = 0;
};

#endif //CONTINUOUSPROCESSING_OPERATOR_H
