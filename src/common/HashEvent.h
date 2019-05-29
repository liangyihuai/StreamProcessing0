//
// Created by USER on 12/4/2018.
//

#ifndef CONTINUOUSPROCESSING_HASHEVENT_H
#define CONTINUOUSPROCESSING_HASHEVENT_H


#include <unordered_map>
#include <set>
#include <map>
#include <sstream>
#include <memory>
#include "Event.h"
#include <string>

using namespace std;

class HashEvent: public Event{
private:
    unordered_map<string, string> attrMap;
public:
	HashEvent(long id, long long time);
    long getId() override{ return getInt("id"); }
    long long getTime() override;
    int getInt(string attrName) override;
    float getFloat(string attrName)override;
    string getString(string attrName)override;
    void print(ostream& out) override;
	string toString()override;

	//it returns: current attributes + extension attributes
	Event* extend(const map<string, string> &extendedEntry) override;

    void addAttr(string attrName, int value);
    void addAttr(string attrName, float value);
    void addAttr(string attrName, string value);
	void setDestination(string _destination);
};

#endif //CONTINUOUSPROCESSING_HASHEVENT_H
