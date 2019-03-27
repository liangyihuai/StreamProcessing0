//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_RADARDERIVEDEVENT_H
#define CONTINUOUSPROCESSING_RADARDERIVEDEVENT_H

#include "DerivedEvent.h"

class RadarDerivedEvent: public DerivedEvent{
private:
    string streamName;
public:

    RadarDerivedEvent(const EventPtr &e, const string streamName) : DerivedEvent(e), streamName(streamName) {}

    std::string getStreamName(){
        return streamName;
    }
};

#endif //CONTINUOUSPROCESSING_RADARDERIVEDEVENT_H
