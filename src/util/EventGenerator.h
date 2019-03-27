#pragma once

#include "Utils.h"
#include "../execution/event/RadarEvent.h"
#include "../common/HashEvent.h"

class EventGenerator {
private:

public:

	static EventPtr generateEvent0() {
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

	static EventPtr generateEvent() {
		HashEvent* e = new HashEvent(Utils::id++, Utils::getTime());
		if (Utils::id % 2 == 0) {
			e->addAttr("iff", "ally");
		}
		else {
			e->addAttr("iff", "unknown");
		}
		//e->setElectromagnetic(0);
		e->addAttr("electromagnetic", 0);
		//e->setElevationAngle((float)Utils::randomFloat(0, 90));
		e->addAttr("elevationAngle", (float)Utils::randomFloat(0, 90));
		//e->setSpeed((float)Utils::randomFloat(-10, 800));
		e->addAttr("speed", (float)Utils::randomFloat(-10, 800));
		//e->setLon((float)Utils::randomFloat(127, 129));
		e->addAttr("lon", (float)Utils::randomFloat(127, 129));
		//e->setLat((float)Utils::randomFloat(35, 37));
		e->addAttr("lat", (float)Utils::randomFloat(35, 37));
		//e->setDirection((float)Utils::randomFloat(0, 360));
		e->addAttr("dir", (float)Utils::randomFloat(0, 360));
		//e->setElevation((float)Utils::randomFloat(-300, 10000));
		float ele = (float)Utils::randomFloat(-300, 10000);
		e->addAttr("elevation", ele);
		e->addAttr("ele", ele);

		return EventPtr (e);
	}
};
