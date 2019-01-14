//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_GREATERTHANFLOAT_H
#define CONTINUOUSPROCESSING_GREATERTHANFLOAT_H

#include "Predicate.h"
#include "Event.h"

class GreaterThanFloat : public Predicate {
private:
    float value;
    string attrName;
    string stream;
public:
    GreaterThanFloat(float value, string attrName, string streamName="") {
        this->value = value;
        this->attrName = attrName;
        this->stream = streamName;
    }

    bool check(EventPtr e) {
        return check("", e);
    }

    bool check(string stream, EventPtr& e){
        if(this->stream != stream) return false;
        return e->getFloat(attrName) > value;
    }

    vector<Predicate*>* getChildren() { return nullptr; };
    void setChildren(vector<Predicate*>* children) {};
    string getTreeObjectName() { return nullptr; };
    void setTreeObjectName(string objectName) {};
};
#endif //CONTINUOUSPROCESSING_GREATERTHANFLOAT_H
