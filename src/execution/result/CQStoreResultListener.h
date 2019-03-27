//
// Created by USER on 12/6/2018.
//

#ifndef CONTINUOUSPROCESSING_STORERESULTLISTENER_H
#define CONTINUOUSPROCESSING_STORERESULTLISTENER_H

#include "ResultListener.h"
#include "../../buffer/DerivedEventStore.h"
#include "../event/DerivedEvent.h"

class CQStoreResultListener: public ResultListener{
    //string stream;
public:
   // CQStoreResultListener(string streamName): stream(streamName){}

    void update(ResultPtr result){
        DerivedEventPtr derivedEventPtr = result->getDerivedEvent();
        DerivedEventStore::addEvent(derivedEventPtr->getStreamName(), derivedEventPtr->getEvent());
    }

};

#endif //CONTINUOUSPROCESSING_STORERESULTLISTENER_H
