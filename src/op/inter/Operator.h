//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_OPERATOR_H
#define CONTINUOUSPROCESSING_OPERATOR_H

#include "../../execution/result/Result.h"

template <class T>
class Operator {
public:
	//perform the procedure to generate results.
    virtual ResultPtr<T> result(EventPtr event) = 0;
};

#endif //CONTINUOUSPROCESSING_OPERATOR_H
