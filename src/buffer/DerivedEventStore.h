//
// Created by USER on 12/4/2018.
//

#ifndef CONTINUOUSPROCESSING_DERIVEDEVENTSTORE_H
#define CONTINUOUSPROCESSING_DERIVEDEVENTSTORE_H

#include <unordered_map>
#include "Queue.h"
#include "QueueWriter.h"
#include "QueueReader.h"
#include <set>
#include <list>
#include "../common/Event.h"


class DerivedEventStore {
    friend class ExecuteScheduler;
private:
    //stream name -> shared queue writer
    static std::unordered_map<std::string, QueueWriter*> queueWriterMap;

    //static unsigned int sharedQueueID;

    //store stream name that is not empty, currently, only add element to it, no deletion.
    static std::set<std::string> unemptyStreams;

    //stream name -> share queue reader
    static std::unordered_map<std::string, std::list<QueueReader*>*> queueReaderMap;

public:

    static void addEvent(std::string stream, EventPtr e);

    static void registerReader(string stream, QueueReader* reader);

    ~DerivedEventStore();
};



#endif //CONTINUOUSPROCESSING_DERIVEDEVENTSTORE_H
