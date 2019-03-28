#pragma once

#include "../../common/Event.h"
#include "../inter/StatefulOperator.h"

template <typename T>
class Window{
public:
	//evict those events that are expired.
	virtual void refresh() = 0;

	virtual void reevaluate(T& result) = 0;

	//add an event to the back side of the window (queue)
	virtual bool push_back(EventPtr e) = 0;

	//return the event in the front of the window
	virtual EventPtr front() = 0;

	//check whether the window is empty or not
	virtual bool empty() = 0;

	//
    virtual int size() = 0;

	//clone the window, including the events insides it.
    virtual Window* clone() = 0;

	virtual void setStatefulOperator(StatefulOperator<T>* op) = 0;
};

