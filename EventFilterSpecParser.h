#pragma once

#include "stdafx.h"

#include "Condition.h"
#include "EventFilterSpec.h"
#include "EventFilterSpec.h"
#include "EventCapture.h"
#include "CEPSpec.h"
#include "OperatorRegister.h"
#include "BoolOpPredicate.h"
#include "GreatThanOpPreDouble.h"
#include "LessThanOpPreDouble.h"
#include "Predicate.h"

/*
//Sample: 
	If not duplicate(id) & not unusual(iff) & not unusual(speed)
	From rawData
	Then targetData
*/
class EventFilterParser {
public:
	static list<EventFilterSpec*> parseAllEventFilterSpec(const list<string> allCQSpecs);

	static EventFilterSpec* parseOneEventFilterSpec(list<string> specStr);
};

