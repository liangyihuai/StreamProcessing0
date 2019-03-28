//
// Created by USER on 12/6/2018.
//

#ifndef CONTINUOUSPROCESSING_MULSTREAMRESULT_H
#define CONTINUOUSPROCESSING_MULSTREAMRESULT_H

#include "Result.h"
#include "../../util/Utils.h"
#include "../../common/HashEvent.h"

//the result contains multiple derived events may with different stream names.
class MultEventResult : public Result {
	vector<EventPtr> derivedEvents;

public:
	vector<EventPtr> getEventVec()override {
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

typedef shared_ptr<MultEventResult> MultEventResultPtr;

#endif //CONTINUOUSPROCESSING_MULSTREAMRESULT_H
