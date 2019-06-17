#include "../stdafx.h"

#include "ApproachingOP.h"
#include "../execution/result/BoolResult.h"

ApproachingOP::ApproachingOP(int min_step, float min_speed, float lon, float lat) {
	this->minStep = min_step;
	this->minSpeed = min_speed;
	this->lon = lon;
	this->lat = lat;

	for (int i = 0; i < Utils::movingObject_id_total_numble; i++) {
		historySteps.push_back(0);
		lon_previous_steps.push_back(-1);
		lat_previous_steps.push_back(-1);
	}
}

bool ApproachingOP::moving_forwards(EventPtr event) {
	int objectId = event->getInt("objid");

	if (historySteps[objectId] == 0) {
		return false;
	}

	float previous_lon = lon_previous_steps[objectId];
	float previous_lat = lat_previous_steps[objectId];
	float curr_lon = event->getFloat("lon");
	float curr_lat = event->getFloat("lat");

	if (pow(curr_lon - lon, 2) + pow(curr_lat - lat, 2) < pow(previous_lon - lon, 2) + pow(previous_lat - lat, 2)) {
		return true;
	}
	return false;
}

ResultPtr ApproachingOP::result(EventPtr event) {
	int objectId = event->getInt("objid");
	int processedStep = historySteps[objectId];

	if (event->getFloat("speed") < minSpeed) {
		historySteps[objectId] = 0;
		return ResultPtr(new BoolResult(false));
	}else if (historySteps[objectId] == 0 && event->getFloat("speed") >= minSpeed) {
		lon_previous_steps[objectId] = event->getFloat("lon");
		lat_previous_steps[objectId] = event->getFloat("lat");
		historySteps[objectId]++; 
		return ResultPtr(new BoolResult(false));
	}else if (moving_forwards(event)) {
		lon_previous_steps[objectId] = event->getFloat("lon");
		lat_previous_steps[objectId] = event->getFloat("lat");
		historySteps[objectId]++;
		if (historySteps[objectId] < minStep) {
			return ResultPtr(new BoolResult(false));
		}else {
			return ResultPtr(new BoolResult(true));
		}
	}else {//not move forwards to the target location.
		return ResultPtr(new BoolResult(false));
	}
}