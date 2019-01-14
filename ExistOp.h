//
// Created by USER on 12/6/2018.
//

#ifndef CONTINUOUSPROCESSING_EXISTOP_H
#define CONTINUOUSPROCESSING_EXISTOP_H

#include "Operator.h"
#include "DerivedEventStore.h"

class ExistOp:public Operator{
private:
	string streamName;
public:
	ExistOp(string _streamName);

	ResultPtr result(EventPtr event);
};


#endif //CONTINUOUSPROCESSING_EXISTOP_H
