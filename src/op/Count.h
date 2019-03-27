//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_COUNT_H
#define CONTINUOUSPROCESSING_COUNT_H

#include "StatefulOperator.h"

class Count : public StatefulOperator {
private:
    long count = 0;
    Window * window = nullptr;

public:
    Count() {}
    ~Count();

    //override
    void setWindow(Window* win) {
        this->window = win;
    }

    ResultPtr result(EventPtr event);
    ResultPtr resultMultEvents(list<EventPtr> *eventList, bool isReset);

    StatefulOperator* clone();
};


#endif //CONTINUOUSPROCESSING_COUNT_H
