#pragma once

#include "Result.h"
#include "../../util/Utils.h"
#include "../../common/HashEvent.h"

//the result contains multiple derived events may with different stream names.
class MultEventResult : public Result<EventPtr> {
	vector<EventPtr> derivedEvents;

public:
	vector<EventPtr> getResultVec()override {
		return derivedEvents;
	}

	void addDeriveEventPtr(EventPtr e) {
		derivedEvents.push_back(e);
	}

	void addDeriveEventPtr(string s) {
		EventPtr newEvent(new HashEvent(Utils::id++, Utils::getTime()));
		newEvent->setDestination(s);
		derivedEvents.push_back(newEvent);
	}
};
