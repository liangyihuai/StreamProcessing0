//
// Created by USER on 12/4/2018.
//

#ifndef CONTINUOUSPROCESSING_EVENTPROCESS_H
#define CONTINUOUSPROCESSING_EVENTPROCESS_H

#include <iostream>
#include "Process.h"
#include <unordered_set>
#include <list>
#include "Event.h"

using namespace std;

class EventProcess: public Process {
private:
	//name of input stream
	string inputStream;

	//name of output stream
	string outputStream;

    unordered_set<string> set;//for deduplication
    list<EventPtr> queue;//for deduplication
    string deduplicationField;//the field name that make deduplication
    int deduplicateBufferSize;
    list<string> unusualFieldNames;
public:

	EventProcess(int deduplicateBufferSize = 10);
	~EventProcess();

	void setDeduplicationField(string field);

	void addUnusualName(string name);

    //filter the incoming events based on the "deduplicatedFiled" and "unusualFieldNames" setup.
	bool filter(EventPtr e);

	void setInputStream(string name) {
		this->inputStream = name;
	}

	void setOutputStream(string name) {
		this->outputStream = name;
	}
private:
    //if the actual event number is greater than deduplicateBufferSize, remove the old event
	void removeOldEvent();

	bool isDuplicated(EventPtr e);

	bool isUnusual(EventPtr e, string field);
};
#endif //CONTINUOUSPROCESSING_EVENTPROCESS_H
