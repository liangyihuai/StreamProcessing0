//
// Created by USER on 12/5/2018.
//
#include "../../stdafx.h"
#include "RadarEvent.h"


RadarEvent::RadarEvent(long id, long long time) {
	this->id = id;
	this->time = time;
}


void RadarEvent::setId(long id) {
	RadarEvent::id = id;
}

void RadarEvent::setTime(long long int time) {
	RadarEvent::time = time;
}

float RadarEvent::getSpeed() const {
	return speed;
}

void RadarEvent::setSpeed(float s) {
	this->speed = s;
}

float RadarEvent::getDirection() const {
	return direction;
}

float RadarEvent::getElevation() const {
	return elevation;
}

float RadarEvent::getElevationAngle() const {
	return elevationAngle;
}

void RadarEvent::setElevationAngle(float elevationAngle) {
	RadarEvent::elevationAngle = elevationAngle;
}

float RadarEvent::getElectromagnetic() const {
	return electromagnetic;
}

void RadarEvent::setElectromagnetic(float electromagnetic) {
	RadarEvent::electromagnetic = electromagnetic;
}

void RadarEvent::setElevation(float elevation) {
	RadarEvent::elevation = elevation;
}

void RadarEvent::setLon(float lon) {
	RadarEvent::lon = lon;
}

void RadarEvent::setLat(float lat) {
	RadarEvent::lat = lat;
}

void RadarEvent::setDirection(float dir) {
	this->direction = dir;
}

string RadarEvent::getIff() const {
	return iff;
}

void RadarEvent::setIff(string iff) {
	RadarEvent::iff = iff;
}

float RadarEvent::getLon() const {
	return lon;
}

float RadarEvent::getLat() const {
	return lat;
}

long RadarEvent::getId() {
	return id;
}

long long RadarEvent::getTime() {
	return time;
}

int RadarEvent::getInt(string attrName) {
	std::cout << "no such attribute or not float type, the attrName is: " << attrName;
	throw runtime_error("");
}

float RadarEvent::getFloat(string attrName) {
	if ("lon" == attrName) {
		return this->lon;
	}
	else if ("lat" == attrName) {
		return this->lat;
	}
	else if ("ele" == attrName || "elevation" == attrName) {
		return this->elevation;
	}
	else if ("speed" == attrName) {
		return this->speed;
	}
	else if ("dir" == attrName || "direction" == attrName) {
		return this->direction;
	}
	else if ("elevationAngle" == attrName) {
		return this->elevationAngle;
	}
	else if ("electromagnetic" == attrName) {
		return this->electromagnetic;
	}
	else if ("iff" == attrName) {
		//return this->iff;
		std::cout << "the type of IFF is string, it is: " << attrName;
		throw runtime_error("");
	}
	else {
		std::cout << "no such attribute or not float type, the attrName is: " << attrName;
		throw "";
	}
}

string RadarEvent::getString(string attrName) {
	if (attrName == "iff") return iff;

	string result;
	if (attrName == "id") {
		return to_string(id);
	}
	else if (attrName == "time") {
		return to_string(time);
	}
	else {
		stringstream ss;
		ss << getFloat(attrName);
		ss >> result;
		return result;
	}
}

string RadarEvent::toString() {
	stringstream msg;
	msg << getId() << ", time:";
	msg << getTime() << ", speed:";
	msg << getFloat("speed") << ", lon:";
	msg << getFloat("lon") << ", lat:";
	msg << getFloat("lat") << ", ele:";
	msg << getFloat("ele") << ", dir:";
	msg << getFloat("dir") << ", eleAngle:";
	msg << getFloat("elevationAngle") << ", elec:";
	msg << getFloat("electromagnetic") << ", iff:";
	msg << getString("iff") << ",";
	return msg.str();
}


//friend ostream& operator << (ostream&, RadarEvent&);

void RadarEvent::print(ostream& out) {
	out << toString();
}

void RadarEvent::setDestination(string _destination) {
	destination = _destination;
}

//add more attributes "extendedEntry" to the copy of current event.
Event* RadarEvent::extend(const map<string, string>& extendedEntry) {
	cout << "radar event, not implemented." << endl;
	throw runtime_error("");
};