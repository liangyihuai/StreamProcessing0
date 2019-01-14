//
// Created by USER on 12/6/2018.
//

#ifndef CONTINUOUSPROCESSING_OPERATORPREDICATE_H
#define CONTINUOUSPROCESSING_OPERATORPREDICATE_H

#include "Event.h"
#include "Predicate.h"

class OperatorPredicate: public Predicate{
public:
    virtual bool check(EventPtr e) = 0;

    vector<Predicate*>* getChildren(){
		LOG(ERROR) << "not implemented";
		throw "not implemented";
	}

    void setChildren(vector<Predicate*>* children){
		LOG(ERROR) << "not implemented";
		throw "not implemented"; 
	}

    string getTreeObjectName(){ 
		LOG(ERROR) << "not implemented"; 
		throw "not implemented";
	}

    void setTreeObjectName(string objectName){
		LOG(ERROR) << "not implemented"; 
		throw "not implemented"; 
	}

    bool check(string stream, EventPtr& e){
		LOG(ERROR) << "not implemented";
		throw "not implemented"; 
	}
};

#endif //CONTINUOUSPROCESSING_OPERATORPREDICATE_H
