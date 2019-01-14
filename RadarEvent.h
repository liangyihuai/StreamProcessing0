//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_RADAREVENT_H
#define CONTINUOUSPROCESSING_RADAREVENT_H

#include <list>
#include <iostream>
#include <sstream>
#include <set>
#include "Event.h"
#include <stdexcept>
#include <limits.h>
#include "glog\logging.h"

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

	RadarEvent(long id, long long time) {
		this->id = id;
		this->time = time;
	}


    void setId(long id) {
        RadarEvent::id = id;
    }

    void setTime(long long int time) {
        RadarEvent::time = time;
    }

    float getSpeed() const {
        return speed;
    }

    void setSpeed(float s){
        this->speed = s;
    }

    float getDirection() const {
        return direction;
    }

    float getElevation() const {
        return elevation;
    }

    float getElevationAngle() const {
        return elevationAngle;
    }

    void setElevationAngle(float elevationAngle) {
        RadarEvent::elevationAngle = elevationAngle;
    }

    float getElectromagnetic() const {
        return electromagnetic;
    }

    void setElectromagnetic(float electromagnetic) {
        RadarEvent::electromagnetic = electromagnetic;
    }

    void setElevation(float elevation) {
        RadarEvent::elevation = elevation;
    }

    void setLon(float lon) {
        RadarEvent::lon = lon;
    }

    void setLat(float lat) {
        RadarEvent::lat = lat;
    }

    void setDirection(float dir){
        this->direction = dir;
    }

    string getIff() const {
        return iff;
    }

    void setIff(string iff) {
        RadarEvent::iff = iff;
    }

    float getLon() const {
        return lon;
    }

    float getLat() const {
        return lat;
    }

	long getId() {
		return id;
	}

	long long getTime() {
		return time;
	}

	int getInt(string attrName) {
		LOG(ERROR) << "no such attribute or not float type, the attrName is: "<<attrName;
		throw runtime_error("");
	}

	float getFloat(string attrName) {
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
		}else if("elevationAngle" == attrName){
		    return this->elevationAngle;
		}else if("electromagnetic" == attrName){
		    return this->electromagnetic;
		}else if("iff" == attrName){
		    //return this->iff;
			LOG(ERROR) << "the type of IFF is string, it is: " << attrName;
		    throw runtime_error("");
		}else {
			LOG(ERROR) << "no such attribute or not float type, the attrName is: " << attrName;
			throw "";
		}
	}

	string getString(string attrName) {
        if(attrName == "iff") return iff;

        string result;
        if(attrName=="id"){
			return to_string(id);
        }else if(attrName == "time"){
			return to_string(time);
		}else {
			stringstream ss;
			ss << getFloat(attrName);
			ss >> result;
			return result;
		}
	}

	//friend ostream& operator << (ostream&, RadarEvent&);

	void print(ostream& out) {
		stringstream msg;
		msg << getId() << ", type:";
		msg << getTime() << ", speed:";
		msg << getFloat("speed") << ", lon:";
		msg << getFloat("lon") << ", lat:";
		msg << getFloat("lat") << ", ele:";
		msg << getFloat("ele") << ", dir:";
		msg << getFloat("dir") << ", eleAngle:";
		msg << getFloat("elevationAngle") << ", elec:";
		msg << getFloat("electromagnetic") << ", iff:";
		msg << getString("iff") << ",";
		out << msg.str();
	}
};


#endif //CONTINUOUSPROCESSING_RADAREVENT_H
