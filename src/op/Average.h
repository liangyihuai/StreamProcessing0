//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_AVERAGE_H
#define CONTINUOUSPROCESSING_AVERAGE_H

#include "../execution/result/Result.h"
#include "../execution/win/Window.h"
#include "../execution/result/DoubleResult.h"

class Average : public StatefulOperator {
private:
    double sum = 0.0;
    int count = 0;
    string attrName;
    Window * window = nullptr;
public:
    Average(string attrName) :attrName(attrName) {}

    //override
    void setWindow(Window *win) {
        this->window = win;
    }

    ResultPtr result(EventPtr event);

    ResultPtr resultMultEvents(list<EventPtr> *eventList, bool isReset);

    StatefulOperator* clone();

    ~Average() { delete window; }
};


#endif //CONTINUOUSPROCESSING_AVERAGE_H
