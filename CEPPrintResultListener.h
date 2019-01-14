#pragma once
#include "ResultListener.h"
#include "DerivedEventStore.h"
#include "MulStreamResult.h"
#include "Utils.h"

class CEPPrintResultListener : public ResultListener {
	//string stream;
public:
	// CQStoreResultListener(string streamName): stream(streamName){}

	void update(ResultPtr result) {
		vector<DerivedEventPtr> eventVec = result->getDerivedEventVec();
		for (DerivedEventPtr ePtr : eventVec) {
			string streamName = ePtr->getStreamName();
			cout << "----------> time: " << Utils::getTime() << ", complexEvent: " << streamName << endl;

			//cout << endl << streamName << ", " << *(ePtr->getEvent()) << endl;
		}
	}

};