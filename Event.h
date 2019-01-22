//
// Created by USER on 12/4/2018.
//

#ifndef CONTINUOUSPROCESSING_EVENT_H
#define CONTINUOUSPROCESSING_EVENT_H
#include <iostream>
#include <set>
#include <memory>
#include "glog\logging.h"
#include "Consts.h"

using namespace std;
//using namespace google;

/**
 * A simple attribute
 */
typedef struct EventAttribute {
	string name;
	ValType type;
	union {
		int intVal;
		float floatVal;
		bool boolVal;
		string stringVal;
	};
} Attribute;

enum EventType {
	EVENT_MSG, TIME_SLIDING_MSG
};

class Event {
public:
	EventType getEventType() { return eventType; }
	void setEventType(EventType type) { this->eventType = type; }

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

	virtual string toString() = 0;

private:
    friend std::ostream& operator<< (std::ostream& os, Event& e);

	//event message or control message, event msg in default.
	EventType eventType = EVENT_MSG;
};


typedef shared_ptr<Event> EventPtr;
#endif //CONTINUOUSPROCESSING_EVENT_H
