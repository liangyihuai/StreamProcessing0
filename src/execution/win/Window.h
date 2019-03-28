//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_QUERYWINDOW_H
#define CONTINUOUSPROCESSING_QUERYWINDOW_H

#include "../../common/Event.h"
#include "../../op/inter/StatefulOperator.h"

class StatefulOperator;

class Window {
public:
    virtual long aggregateLongValue(EventPtr incomeEvent, StatefulOperator * op) = 0;
    virtual double aggregateDoubleValue(EventPtr incomeEvent, StatefulOperator * op) = 0;

    virtual int getCountLen() = 0;
    virtual int getCountSliding() = 0;

    virtual int size() = 0;

    virtual Window* clone() = 0;
};

#endif //CONTINUOUSPROCESSING_QUERYWINDOW_H
