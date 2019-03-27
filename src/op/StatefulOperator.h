//
// Created by USER on 12/5/2018.
//

#include "../execution/win/Window.h"

#ifndef CONTINUOUSPROCESSING_STATEFULOPERATOR_H
#define CONTINUOUSPROCESSING_STATEFULOPERATOR_H

#include "Operator.h"
#include <list>
#include "../buffer/SharedQueueReader.h"

class Window;//避免相互嵌套引用，比如A包含了B，B又包含了A

class StatefulOperator :public Operator{
public:
    virtual ResultPtr resultMultEvents(list<EventPtr> *eventList, bool isReset) = 0;

    virtual void setWindow(Window * win) = 0;

    virtual StatefulOperator* clone() = 0;
};

#endif //CONTINUOUSPROCESSING_STATEFULOPERATOR_H
