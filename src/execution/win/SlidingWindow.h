//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_SLIDINGWINDOW_H
#define CONTINUOUSPROCESSING_SLIDINGWINDOW_H


#include "Window.h"
#include "../../execution/result/Result.h"
#include <list>

class SlidingWindow: public Window {
private:
    int winLen;
    int slidingLen = 1;
    list<EventPtr> eventList;
public:
    SlidingWindow(int windowLen, int slidingLen) {
        this->winLen = windowLen;
        this->slidingLen = slidingLen;
    }

    //override
    double aggregateDoubleValue(EventPtr incomeEvent, StatefulOperator * op) {
        eventList.push_back(incomeEvent);
        while (eventList.size() > winLen) {
            eventList.pop_front();
        }
        ResultPtr result = op->resultMultEvents(&eventList, true);
        return result->getDouble();
    }

    //override
    long aggregateLongValue(EventPtr incomeEvent, StatefulOperator * op) {
        eventList.push_back(incomeEvent);
        while (eventList.size() > winLen) {
            eventList.pop_front();
        }

        ResultPtr result = op->resultMultEvents(&eventList, true);
        return result->getLong();
    }

    int getCountLen() {
        return this->winLen;
    }
    int getCountSliding() {
        return this->slidingLen;
    }
    int size() {
        return eventList.size();
    }

    Window* clone() {
        SlidingWindow * newWin = new SlidingWindow(this->winLen, this->slidingLen);
        return newWin;
    }

    ~SlidingWindow(){}
};

#endif //CONTINUOUSPROCESSING_SLIDINGWINDOW_H
