//
// Created by USER on 12/4/2018.
//

#ifndef CONTINUOUSPROCESSING_EVENTCAPTURE_H
#define CONTINUOUSPROCESSING_EVENTCAPTURE_H


#include "Condition.h"
#include "ResultListener.h"
#include "DerivedEventStore.h"
#include "Process.h"


class EventCapture: public Process{
private:
    Condition condition;
	string inputStream;
    string outputStream;

public:
    void setCondition(Condition condition){
        this->condition = condition;
    }

	void setInputStream(string name) {
		this->inputStream = name;
	}

    void setOutputStream(string name){
        this->outputStream = name;
    }

    bool process(EventPtr e){
        if(condition.check(e)){//meet the condition
            DerivedEventStore::addEvent(outputStream, e);
            return true;
        }
        return false;
    }

   // ~EventCapture(){};
};


#endif //CONTINUOUSPROCESSING_EVENTCAPTURE_H
