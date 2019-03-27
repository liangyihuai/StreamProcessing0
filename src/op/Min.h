//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_MIN_H
#define CONTINUOUSPROCESSING_MIN_H

#include "../execution/result/Result.h"
#include "../common/Event.h"
#include "StatefulOperator.h"
#include "../execution/result/DoubleResult.h"

class Min : public StatefulOperator {
    float min = 99999;
    Window * window = nullptr;
    string attr;
public:
    Min(string attrName) :attr(attrName) {}
    ~Min() { delete window; }

    //override
    void setWindow(Window* win) { this->window = win; }
    //override
    ResultPtr result(EventPtr event);
    //override
    ResultPtr resultMultEvents(list<EventPtr> *eventList, bool isReset);
    //override
    StatefulOperator* clone();
};

#endif //CONTINUOUSPROCESSING_MIN_H
