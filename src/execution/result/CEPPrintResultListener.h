#pragma once
#include "ResultListener.h"


class CEPPrintResultListener : public ResultListener<EventPtr> {
public:
	void update(ResultPtr<EventPtr>& result) {
		vector<EventPtr> eventVec = result->getResultVec();
		for (EventPtr ePtr : eventVec) {
			string streamName = ePtr->getDestination();
			cout << "---> time: " << Utils::getTime() << ", complexEvent: " << streamName << endl;
		}
	}

};