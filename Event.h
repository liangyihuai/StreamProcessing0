//
// Created by USER on 12/4/2018.
//

#ifndef CONTINUOUSPROCESSING_EVENT_H
#define CONTINUOUSPROCESSING_EVENT_H
#include <iostream>
#include <set>
#include <memory>
#include "glog\logging.h"

using namespace std;
//using namespace google;

class Event {
public:
    virtual long getId(){ return 0L;};

    virtual long long getTime() {return 0LL;};

    virtual int getInt(string attrName){
		LOG(ERROR) << "function size is not implemented";
        throw runtime_error("");
    }

    virtual float getFloat(string attrName){
		LOG(ERROR) << "function size is not implemented";
        throw runtime_error("");
    }

    virtual string getString(string attrName){
		LOG(ERROR) << "function size is not implemented";
        throw runtime_error("");
    }

    virtual void print(ostream& out){
		LOG(ERROR) << "function size is not implemented";
        throw runtime_error("");
    }

private:
    friend std::ostream& operator<< (std::ostream& os, Event& e);
};


typedef shared_ptr<Event> EventPtr;
#endif //CONTINUOUSPROCESSING_EVENT_H
