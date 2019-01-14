#pragma once

#include "Utils.h"
#include "RadarEvent.h"

class EventGenerator {
private:

public:

	static EventPtr generateEvent() {
		RadarEvent* e = new RadarEvent(Utils::id++, Utils::getTime());
		if (Utils::id % 2 == 0) {
			e->setIff("ally");
		}
		else {
			e->setIff("unknown");
		}
		e->setElectromagnetic(0);
		e->setElevationAngle((float)Utils::randomFloat(0, 90));
		e->setSpeed((float)Utils::randomFloat(-10, 800));
		e->setLon((float)Utils::randomFloat(127, 129));
		e->setLat((float)Utils::randomFloat(35, 37));
		e->setDirection((float)Utils::randomFloat(0, 360));
		e->setElevation((float)Utils::randomFloat(-300, 10000));
		EventPtr ep(e);
		return ep;
	}
};
