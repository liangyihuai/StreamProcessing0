//
// Created by USER on 12/4/2018.
//
#include "stdafx.h"
#include "HashEvent.h"


int HashEvent::getInt(string attrName)  {
    if (attrMap.find(attrName) != attrMap.end()) {
        stringstream stream;
        stream << attrMap[attrName];
        int int_temp = 0;
        stream >> int_temp;
        return int_temp;
    }
    else {
		LOG(ERROR) << "no this element";
        throw "";
    }
}

float HashEvent::getFloat(string attrName)  {
    if (attrMap.find(attrName) != attrMap.end()) {
        stringstream stream(attrMap[attrName]);
        float int_temp = 0;
        stream >> int_temp;
        return int_temp;
    }
    else {
		LOG(ERROR) << "no this element";
        throw "";
    }
}

string HashEvent::getString(string attrName)  {
    if (attrMap.find(attrName) != attrMap.end()) {
        return attrMap[attrName];
    }
    else {
		LOG(ERROR) << "no this element";
        throw "no this element";
    }
}

void HashEvent::addAttr(string attrName, int value) {
    if (attrMap.find(attrName) != attrMap.end()) {
		LOG(ERROR) << "already exist the name";
        throw runtime_error("");
    }
    attrMap[attrName] = to_string(value);
}

void HashEvent::addAttr(string attrName, float value) {
    if (attrMap.find(attrName) != attrMap.end()) {
		LOG(ERROR) << "already exist the name";
        throw "already exist the name";
    }
    attrMap[attrName] = to_string(value);
}

void HashEvent::addAttr(string attrName, string value) {
    if (attrMap.find(attrName) != attrMap.end()) {
		LOG(ERROR) << "already exist the name";
        throw "already exist the name";
    }
    attrMap[attrName] = value;
}

void HashEvent::setGroupName(string groupName) {
    this->eventGroupName = groupName;
}

bool HashEvent::belongToGroup(string groupName) {
    return this->eventGroupName == groupName;
}

long long HashEvent::getTime() {
    string timeStr = getString("time");
    stringstream s(timeStr);
    long long result = 0;
    s >> result;
    return result;
};

void HashEvent::print(ostream& out) {
    stringstream msg;
    msg << this->getId() << ",";
    msg <<this->getTime() << ",";
    msg << this->getEventType() << ",";
    msg << this->getGroupName();
    msg << "," << attrMap["dir"];
    msg << "," << attrMap["speed"];
    msg << "," << attrMap["ele"];
    msg << "," << attrMap["lon"];
    msg << "," << attrMap["lat"];
    out << msg.str();
}

//
//void HashEvent::print(ostream& out) {
//	stringstream msg;
//	msg << this->getId() << ", ";
//	msg << this->getEventType() << ", ";
//	msg << this->getTime() << ", group[";
//	for (string g : this->groups) {
//		msg << g << ", ";
//	}
//	msg << "]";
//
//	map<string, string>::iterator iter = this->attrMap.begin();
//	while (iter != this->attrMap.end()) {
//		if (iter->first != "id" && iter->first != "eventType" && iter->first != "time") {
//			msg << ", " << iter->first << ":" << iter->second;
//		}
//		iter++;
//	}
//	out << msg.str();
//}