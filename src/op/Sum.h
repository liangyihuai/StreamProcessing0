//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_SUM_H
#define CONTINUOUSPROCESSING_SUM_H


#include "../execution/win/Window.h"
#include "../execution/result/DoubleResult.h"

class Sum: public StatefulOperator{
private:
    double sum = 0.0;
    string attrName;
    Window * window = nullptr;

public:
    Sum(string attrName):attrName(attrName) {}

    //override
    void setWindow(Window *win) {
        this->window = win;
    }

    ResultPtr result(EventPtr event);

    ResultPtr resultMultEvents(list<EventPtr> *eventList, bool isReset);

    StatefulOperator* clone();

    ~Sum() {delete window;}
};

#endif //CONTINUOUSPROCESSING_SUM_H
