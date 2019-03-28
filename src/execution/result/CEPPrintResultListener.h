#pragma once
#include "ResultListener.h"

class CEPPrintResultListener : public ResultListener {
public:
	void update(ResultPtr result) {
		vector<EventPtr> eventVec = result->getEventVec();
		for (EventPtr ePtr : eventVec) {
			string streamName = ePtr->getDestination();
			cout << "---> time: " << Utils::getTime() << ", complexEvent: " << streamName << endl;
		}
	}

};