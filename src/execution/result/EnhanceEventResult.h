//
// Created by USER on 12/6/2018.
//

#ifndef CONTINUOUSPROCESSING_ENHANCEEVENTRESULT_H
#define CONTINUOUSPROCESSING_ENHANCEEVENTRESULT_H

#include "Result.h"

class EnhanceEventResult : public Result {
private:
	EventPtr e;
	string streamName;
public:
	EnhanceEventResult(EventPtr eventPtr, string stream) {
		this->streamName = stream;
		this->e = eventPtr;
	}

	EventPtr getDerivedEvent() {
		Event* event = e->extend(map<string, string>());
		return EventPtr(event);
	}
};
#endif //CONTINUOUSPROCESSING_ENHANCEEVENTRESULT_H
