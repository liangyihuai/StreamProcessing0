//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_RESULT_H
#define CONTINUOUSPROCESSING_RESULT_H


#include <memory>
#include <stdexcept>
#include "Event.h"
#include "DerivedEvent.h"
#include <vector>
#include "glog\logging.h"

class Result{
public:
    virtual double getDouble(){
		LOG(ERROR) << "function is not implemented";
        throw runtime_error("not implemented");
    };

    virtual long getLong(){
		LOG(ERROR) << "function is not implemented";
        throw runtime_error("not implemented");
    }

    virtual bool getBool(){
		LOG(ERROR) << "function is not implemented";
        throw runtime_error("not implemented");
    }

    virtual EventPtr getEvent(){
		LOG(ERROR) << "function is not implemented";
        throw runtime_error("not implemented");
    }

    virtual vector<EventPtr> getEventVec(){
		LOG(ERROR) << "function is not implemented";
        throw runtime_error("not implemented");
    }

    virtual DerivedEventPtr getDerivedEvent(){
		LOG(ERROR) << "function is not implemented";
        throw runtime_error("not implemented");
    }

    virtual vector<DerivedEventPtr> getDerivedEventVec(){
		LOG(ERROR) << "function is not implemented";
        throw runtime_error("not implemented");
    }

};

typedef shared_ptr<Result> ResultPtr;

#endif //CONTINUOUSPROCESSING_RESULT_H
