#pragma once

#include "ResultListener.h"
#include "DerivedEventStore.h"
#include "MulStreamResult.h"

class CEPStoreResultListener : public ResultListener {
	//string stream;
public:
	// CQStoreResultListener(string streamName): stream(streamName){}

	void update(ResultPtr result) {
		vector<DerivedEventPtr> eventVec = result->getDerivedEventVec();
		for (DerivedEventPtr ePtr : eventVec) {
			string streamName = ePtr->getStreamName();
			DerivedEventStore::addEvent(streamName, ePtr->getEvent());

			//cout << endl << streamName << ", " << *(ePtr->getEvent()) << endl;
		}
	}

};