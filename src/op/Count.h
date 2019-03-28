#pragma once

#include "inter/AggregateOperator.h"

class Count : public AggregateOperator<long> {
private:
    long count = 0;
   
public:
    Count() {}
	~Count() {};

    ResultPtr<long> result(EventPtr event) override;
    ResultPtr<long> resultMultEvents(list<EventPtr> *eventList, bool isReset)override;
};

