//
// Created by USER on 12/4/2018.
//
#include "../stdafx.h"
#include "HashEvent.h"

HashEvent::HashEvent(long id, long long time) {
	stringstream ss;
	ss << id;
	addAttr("id", ss.str());
	stringstream stream;
	stream << time;
	string timeStr;
	stream >> timeStr;
	addAttr("time", timeStr);
}

int HashEvent::getInt(string attrName)  {
    if (attrMap.find(attrName) != attrMap.end()) {
        stringstream stream;
        stream << attrMap[attrName];
        int int_temp = 0;
        stream >> int_temp;
        return int_temp;
    }
    else {
		std::cout << "no this element, attrName is " << attrName;
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
		std::cout << "no this element, attrName is " << attrName;
        throw "";
    }
}

string HashEvent::getString(string attrName)  {
    if (attrMap.find(attrName) != attrMap.end()) {
        return attrMap[attrName];
    }
    else {
		std::cout << "no this element, attrName is "  << attrName;
        throw "no this element";
    }
}

void HashEvent::addAttr(string attrName, int value) {
    if (attrMap.find(attrName) != attrMap.end()) {
		std::cout << "already exist the name";
        throw runtime_error("");
    }
    attrMap[attrName] = to_string(value);
}

void HashEvent::addAttr(string attrName, float value) {
    if (attrMap.find(attrName) != attrMap.end()) {
		std::cout << "already exist the name";
        throw "already exist the name";
    }
    attrMap[attrName] = to_string(value);
}

void HashEvent::addAttr(string attrName, string value) {
    if (attrMap.find(attrName) != attrMap.end()) {
		std::cout << "already exist the name";
        throw "already exist the name";
    }
    attrMap[attrName] = value;
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
    msg << "," << attrMap["dir"];
    msg << "," << attrMap["speed"];
    msg << "," << attrMap["ele"];
    msg << "," << attrMap["lon"];
    msg << "," << attrMap["lat"];
    out << msg.str();
}

string HashEvent::toString() {
	stringstream msg;
	msg << getId() << ", time:";
	msg << getTime() << ", speed:";
	msg << getFloat("speed") << ", lon:";
	msg << getFloat("lon") << ", lat:";
	msg << getFloat("lat") << ", ele:";
	msg << getFloat("elevation") << ", dir:";
	msg << getFloat("dir") << ", eleAngle:";
	msg << getFloat("elevationAngle") << ", elec:";
	msg << getFloat("electromagnetic") << ", iff:";
	msg << getString("iff") << ",";
	return msg.str();
}

void HashEvent::setDestination(string _destination) {
	destination = _destination;
}

Event* HashEvent::extend(const map<string, string>& extendedEntry) {
	HashEvent* he = new HashEvent(getId(), getTime());

	for (auto iter = extendedEntry.begin(); iter != extendedEntry.end(); iter++) {
		he->attrMap[iter->first] = iter->second;
	}
	for (auto iter = attrMap.begin(); iter != attrMap.end(); iter++) {
		he->attrMap[iter->first] = iter->second;
	}
	
	return he;
}
