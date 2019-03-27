//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_RADAREVENT_H
#define CONTINUOUSPROCESSING_RADAREVENT_H

#include <list>
#include <iostream>
#include <sstream>
#include <set>
#include "../../common/Event.h"
#include <stdexcept>
#include <limits.h>

////id, time, speed, direction, elevation, elevation angle, electromagnetic, IFF, location(x, y)
class RadarEvent : public Event {
private:
	long id;
	long long time;
    float speed = -1;
    float direction = -1;
    float elevation = -1;
    float elevationAngle = -1;
    float electromagnetic = -1;
    string iff;//IFF
	float lon = -1;
	float lat = -1;
public:
    RadarEvent(){}

	RadarEvent(long id, long long time);


	void setId(long id);

	void setTime(long long int time);

	float getSpeed() const;

	void setSpeed(float s);

	float getDirection() const;

	float getElevation() const;

	float getElevationAngle() const;

	void setElevationAngle(float elevationAngle);

	float getElectromagnetic() const;

	void setElectromagnetic(float electromagnetic);

	void setElevation(float elevation);

	void setLon(float lon);

	void setLat(float lat);

	void setDirection(float dir);

	string getIff() const;

	void setIff(string iff);

	float getLon() const;

	float getLat() const;

	long getId();

	long long getTime();

	int getInt(string attrName);

	float getFloat(string attrName);

	string getString(string attrName);

	string toString();

	//friend ostream& operator << (ostream&, RadarEvent&);

	void print(ostream& out);

	void setDestination(string _destination);

	//add more attributes "extendedEntry" to the copy of current event.
	Event* extend(const map<string, string>& extendedEntry);
};


#endif //CONTINUOUSPROCESSING_RADAREVENT_H
