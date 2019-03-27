//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_MAX_H
#define CONTINUOUSPROCESSING_MAX_H


#include "StatefulOperator.h"
#include "../execution/result/Result.h"
#include "../execution/result/DoubleResult.h"

//use doubleResult to get the result
class Max : public StatefulOperator {
    float max = -99999999;
    Window * window = nullptr;
    string attr;
public:
    Max(string attrName):attr(attrName) {}
    ~Max() { delete window; }

    //override
    void setWindow(Window* win) {this->window = win;}
    //override
    ResultPtr result(EventPtr event);
    //override
    ResultPtr resultMultEvents(list<EventPtr> *eventList, bool isReset);
    //override
    StatefulOperator* clone();
};



#endif //CONTINUOUSPROCESSING_MAX_H
