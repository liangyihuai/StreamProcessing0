#pragma once

#include "Predicate.h"
#include "Event.h"
#include <list>

//Index interface
class CQIndex {
public:
	//
	virtual void buildIndex(Predicate*, int64_t regionId) = 0;

	virtual list<Process*> filter(EventPtr) = 0;

};

