#pragma once

#include "StatefulOperator.h"
#include "../../execution/result/Result.h"

/*
Interface of Aggregate Operators
*/

template <class T>
class AggregateOperator: public StatefulOperator<T> {
public:
	
};