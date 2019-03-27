#pragma once
#include "ResultListener.h"
#include "../../buffer/DerivedEventStore.h"
#include "MulStreamResult.h"
#include "../../util/Utils.h"

class CEPPrintResultListener : public ResultListener {
	//string stream;
public:
	// CQStoreResultListener(string streamName): stream(streamName){}

	void update(ResultPtr result) {
		vector<EventPtr> eventVec = result->getDerivedEventVec();
		for (EventPtr ePtr : eventVec) {
			string streamName = ePtr->getDestination();
			cout << "----------> time: " << Utils::getTime() << ", complexEvent: " << streamName << endl;

			//cout << endl << streamName << ", " << *(ePtr->getEvent()) << endl;
		}
	}

};