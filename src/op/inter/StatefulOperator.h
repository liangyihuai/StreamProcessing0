#pragma once

#include "Operator.h"
#include <list>
#include "../win/Window.h"

template <typename T>
class StatefulOperator :public Operator<T>{
public:
    virtual ResultPtr<T> resultMultEvents(list<EventPtr> *eventList, bool isReset) = 0;

   // virtual void setWindow(Window<T> * win) = 0;
};