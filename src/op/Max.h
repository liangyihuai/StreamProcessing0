#pragma once

#include "inter/StatefulOperator.h"
#include "../execution/result/Result.h"
#include "../execution/result/DoubleResult.h"

//use doubleResult to get the result
class Max : public StatefulOperator<double> {
    float max = -99999999;
    string attr;
public:
    Max(string attrName):attr(attrName) {}
    ~Max() { }

   
    //override
    ResultPtr<double> result(EventPtr event);
    //override
    ResultPtr<double> resultMultEvents(list<EventPtr> *eventList, bool isReset);
};


