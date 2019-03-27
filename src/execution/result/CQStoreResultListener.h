//
// Created by USER on 12/6/2018.
//

#ifndef CONTINUOUSPROCESSING_STORERESULTLISTENER_H
#define CONTINUOUSPROCESSING_STORERESULTLISTENER_H

#include "ResultListener.h"
#include "../../buffer/DerivedEventStore.h"

class CQStoreResultListener : public ResultListener {
	//string stream;
public:
	// CQStoreResultListener(string streamName): stream(streamName){}

	void update(ResultPtr result) {
		EventPtr derivedEventPtr = result->getDerivedEvent();
		DerivedEventStore::addEvent(derivedEventPtr->getDestination(), derivedEventPtr);
	}

};

#endif //CONTINUOUSPROCESSING_STORERESULTLISTENER_H
