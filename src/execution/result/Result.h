//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_RESULT_H
#define CONTINUOUSPROCESSING_RESULT_H


#include <memory>
#include <stdexcept>
#include "../../common/Event.h"
#include "../event/DerivedEvent.h"
#include <vector>

class Result{
public:
    virtual double getDouble(){
		std::cout << "function is not implemented";
        throw runtime_error("not implemented");
    };

    virtual long getLong(){
		std::cout << "function is not implemented";
        throw runtime_error("not implemented");
    }

    virtual bool getBool(){
		std::cout << "function is not implemented";
        throw runtime_error("not implemented");
    }

    virtual EventPtr getEvent(){
		std::cout << "function is not implemented";
        throw runtime_error("not implemented");
    }

    virtual vector<EventPtr> getEventVec(){
		std::cout << "function is not implemented";
        throw runtime_error("not implemented");
    }

    virtual EventPtr getDerivedEvent(){
		std::cout << "function is not implemented";
        throw runtime_error("not implemented");
    }

    virtual vector<EventPtr> getDerivedEventVec(){
		std::cout << "function is not implemented";
        throw runtime_error("not implemented");
    }

};

typedef shared_ptr<Result> ResultPtr;

#endif //CONTINUOUSPROCESSING_RESULT_H
