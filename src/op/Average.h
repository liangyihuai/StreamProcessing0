#ifndef CONTINUOUSPROCESSING_AVERAGE_H
#define CONTINUOUSPROCESSING_AVERAGE_H

#include "../execution/result/Result.h"
#include "../execution/win/Window.h"
#include "../execution/result/DoubleResult.h"
#include "inter/AggregateOperator.h"

class Average : public AggregateOperator {
private:
    double sum = 0.0;
    int count = 0;
    string attrName;
    Window * window = nullptr;
public:
    Average(string attrName) :attrName(attrName) {}
	~Average() { delete window; }

	void setWindow(Window *win)override;
    ResultPtr result(EventPtr event) override;
    ResultPtr resultMultEvents(list<EventPtr> *eventList, bool isReset) override;
    StatefulOperator* clone()override;
    
};


#endif //CONTINUOUSPROCESSING_AVERAGE_H
