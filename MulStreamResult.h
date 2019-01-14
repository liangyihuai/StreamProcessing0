//
// Created by USER on 12/6/2018.
//

#ifndef CONTINUOUSPROCESSING_MULSTREAMRESULT_H
#define CONTINUOUSPROCESSING_MULSTREAMRESULT_H

#include "Result.h"

//the result contains multiple derived events with different stream name.
class MulStreamResult: public Result{
    vector<DerivedEventPtr> derivedEvents;
public:
    vector<DerivedEventPtr> getDerivedEventVec(){
        return derivedEvents;
    }

    void addDeriveEventPtr(DerivedEventPtr e){
        derivedEvents.push_back(e);
    }

    void addDeriveEventPtr(vector<string> streams){
        for(string s: streams){
			EventPtr newEvent(new RadarEvent(Utils::id++, Utils::getTime()));
            DerivedEventPtr e(new DerivedEvent(newEvent, s));
            derivedEvents.push_back(e);
        }
    }
};

typedef shared_ptr<MulStreamResult> MulStreamResultPtr;

#endif //CONTINUOUSPROCESSING_MULSTREAMRESULT_H
