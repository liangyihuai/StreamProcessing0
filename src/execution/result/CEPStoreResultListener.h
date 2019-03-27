#pragma once

#include "ResultListener.h"
#include "../../buffer/DerivedEventStore.h"
#include "MulStreamResult.h"
#include <vector>
#include <iostream>

class CEPStoreResultListener : public ResultListener {
	//string stream;
public:
	// CQStoreResultListener(string streamName): stream(streamName){}

	void update(ResultPtr result) {
		vector<EventPtr> eventVec = result->getDerivedEventVec();
		for (EventPtr ePtr : eventVec) {
			string streamName = ePtr->getDestination();
			DerivedEventStore::addEvent(streamName, ePtr);

			//cout << endl << streamName << ", " << *(ePtr->getEvent()) << endl;
		}
	}
	
};