#ifndef CONTINUOUSPROCESSING_AVERAGE_H
#define CONTINUOUSPROCESSING_AVERAGE_H

#include "../execution/result/Result.h"
#include "../execution/result/DoubleResult.h"
#include "inter/AggregateOperator.h"

class Average : public AggregateOperator<double> {
private:
    double sum = 0.0;
    long count = 0;
    string attrName;
public:
    Average(string attrName) :attrName(attrName) {}
	~Average() {}

    ResultPtr<double> result(EventPtr event) override;
    ResultPtr<double> resultMultEvents(list<EventPtr> *eventList, bool isReset) override;
};
#endif //CONTINUOUSPROCESSING_AVERAGE_H
