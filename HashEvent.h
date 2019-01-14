//
// Created by USER on 12/4/2018.
//

#ifndef CONTINUOUSPROCESSING_HASHEVENT_H
#define CONTINUOUSPROCESSING_HASHEVENT_H


#include <unordered_map>
#include <set>
#include <sstream>
#include <memory>
#include "Event.h"
#include <string>

using namespace std;

class HashEvent: public Event{
private:
    unordered_map<string, string> attrMap;
    //set<string> groups; //an event could belong to multiple group.
    string eventGroupName;
public:
    HashEvent(long id, string eventType, long long time) {
        stringstream ss;
        ss << id;
        addAttr("id", ss.str());
        addAttr("eventtype", eventType);

        stringstream stream;
        stream << time;
        string timeStr;
        stream >> timeStr;
        addAttr("time", timeStr);
    }
    long getId() { return getInt("id"); }
    long long getTime() ;
    string getEventType() {
        return getString("eventtype");
    }
    bool belongToGroup(string groupName);
    int getInt(string attrName) ;
    float getFloat(string attrName);
    string getString(string attrName);

    void print(ostream& out) ;

    string getGroupName() { return eventGroupName; }

    void addAttr(string attrName, int value);
    void addAttr(string attrName, float value);
    void addAttr(string attrName, string value);
    void setGroupName(string groupName);

};




#endif //CONTINUOUSPROCESSING_HASHEVENT_H
