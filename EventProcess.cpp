//
// Created by USER on 12/4/2018.
//
#include "stdafx.h"
#include "EventProcess.h"

EventProcess::EventProcess(int deduplicateBufferSize) {
	this->deduplicateBufferSize = deduplicateBufferSize;
}

EventProcess::~EventProcess() {}

void EventProcess::setDeduplicationField(string field) {
	this->deduplicationField = field;
}

bool EventProcess::isDuplicated(EventPtr e) {
	if (deduplicationField == "") { 
		LOG(ERROR) << "deduplication Field empty";
		throw ""; 
	}

	bool result = false;
	
	string value;
	value = e->getString(deduplicationField);
	if (set.find(value) != set.end()) {
		result = true;
	}else {
		queue.push_back(e);
		set.insert(value);
	}

	removeOldEvent();
	return result;
}

bool EventProcess::isUnusual(EventPtr e, string field) {
	if (field == "id") {
		if (e->getId() < 0) return true;
	}else if (field == "time") {
		if (e->getTime() < 1000000) return true;
	}
	else if (field=="speed" || field=="ele" || field=="lon" 
		|| field=="lat" || field=="electromagnetic"||field=="dir") {
		if (e->getFloat(field) < 0) 
			return true;
	}
	else if (e->getString(field) == "") return true;
	return false;
}

void EventProcess::addUnusualName(string name) {
	unusualFieldNames.push_back(name);
}

//filter the incoming events based on the "deduplicatedFiled" and "unusualFieldNames" setup.
bool EventProcess::filter(EventPtr e) {
	for (string unusual : unusualFieldNames) {
		bool b = isUnusual(e, unusual);
		if (b) return false;
	}
	if (deduplicationField != "") {
		if (isDuplicated(e)) {
			return false;
		}
	}
	return true;
}

//if the actual event number is greater than deduplicateBufferSize, remove the old event
void EventProcess::removeOldEvent() {
	while (queue.size() > deduplicateBufferSize) {
		EventPtr tempE = queue.front();
		string value = tempE->getString(deduplicationField);
		if (set.find(value) != set.end())
			set.erase(value);
		queue.pop_front();
	}
}