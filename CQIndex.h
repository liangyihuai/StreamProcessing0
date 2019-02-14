#pragma once

#include "Condition.h"
#include "Event.h"
#include <list>

//Index interface
class CQIndex {
public:
	//
	virtual void buildIndex(Condition*) = 0;

	virtual list<Process*> filter(EventPtr) = 0;

	//virtual list<Process*> refine(list<Process*>) = 0;

};

