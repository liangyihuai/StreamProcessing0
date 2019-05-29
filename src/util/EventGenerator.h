#pragma once

#include "Utils.h"
#include "../common/HashEvent.h"

class EventGenerator {
private:

public:

	static EventPtr generateEvent() {
		HashEvent* e = new HashEvent(Utils::id++, Utils::getTime());
		if (Utils::id % 2 == 0) {
			e->addAttr("iff", "ally");
		}
		else {
			e->addAttr("iff", "unknown");
		}
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

		if (Utils::id % 2 == 0) {
			e->addAttr("communicationsetup", true);
		}
		else {
			e->addAttr("communicationsetup", false);
		}

		e->addAttr("elevationangle", (float)Utils::randomFloat(0, 360));
		double ran = ((double)rand())/RAND_MAX;
		if (ran < 0.3) {
			e->addAttr("electromagnetic", "enemy");
		}
		else if (ran < 0.6) {
			e->addAttr("electromagnetic", "neutral");
		}
		else {
			e->addAttr("electromagnetic", "ally");
		}
		return EventPtr (e);
	}
};
