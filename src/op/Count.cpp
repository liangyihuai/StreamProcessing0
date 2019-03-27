//
// Created by USER on 12/5/2018.
//
#include "../stdafx.h"
#include "Count.h"
#include "../execution/result/LongResult.h"

ResultPtr Count::result(EventPtr event) {
    LongResult * result1 = new LongResult();
    count++;
    if (window == nullptr) {
        result1->setValue(count);
    }else {
        result1->setValue(window->aggregateLongValue(event, this));
    }
    return ResultPtr(result1);
}

ResultPtr Count::resultMultEvents(list<EventPtr> *eventList, bool isReset) {
    long tempCount = 0;
    if (!isReset) tempCount = this->count;

    tempCount += eventList->size();

    if (!isReset) this->count = tempCount;

    ResultPtr result(new LongResult(tempCount));
    return result;
}

StatefulOperator* Count::clone() {
    Count * newSumOp = new Count();
    if(window != nullptr)
        newSumOp->window = window->clone();
    return newSumOp;
}
