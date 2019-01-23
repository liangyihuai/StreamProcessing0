#ifndef CONTINUOUSPROCESSING_EVENTPROCESS_H
#define CONTINUOUSPROCESSING_EVENTPROCESS_H

#include <iostream>
#include <unordered_set>
#include <queue>
#include <list>
#include "Event.h"
#include <set>

using namespace std;

class EventProcess{
private:
	//name of input stream
	string inputStream;

	//name of output stream
	string outputStreamName;

	set<queue<EventPtr>*> outputQueueSet;

    unordered_set<string> set;//for deduplication
    list<EventPtr> queueForDeduplication;//for deduplication
    string deduplicationField;//the field name that make deduplication
    int deduplicateBufferSize;
    list<string> unusualFieldNames;
public:

	EventProcess(int deduplicateBufferSize = 10);
	~EventProcess();

	void addOutputQueue(queue<EventPtr>* q);

	void setDeduplicationField(string field);

	void addUnusualName(string name);

    //filter the incoming events based on the "deduplicatedFiled" and "unusualFieldNames" setup.
	void process(EventPtr e);

	void setInputStream(string name);

	void setOutputStreamName(string name);

	string getOutputStreamName();

private:
    //if the actual event number is greater than deduplicateBufferSize, remove the old event
	void removeOldEvent();

	bool isDuplicated(EventPtr e);

	bool isUnusual(EventPtr e, string field);
};
#endif //CONTINUOUSPROCESSING_EVENTPROCESS_H
