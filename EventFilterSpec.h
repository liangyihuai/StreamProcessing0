#pragma once

#include "Spec.h"
#include <list>
#include "EventProcess.h"

class EventFilterSpec : public Spec {
private:
	string inputStream;
	string outputStream;
	string notDuplicateField;
	list<string> notUnusualFieldList;

public:
	EventProcess * instance() {
		EventProcess* eventFilter = new EventProcess();
		for (string field : notUnusualFieldList) {
			eventFilter->addUnusualName(field);
		}
		eventFilter->setDeduplicationField(notDuplicateField);
		eventFilter->setInputStream(inputStream);
		eventFilter->setOutputStream(outputStream);
		return eventFilter;
	}

	void setInputStream(string name) {
		this->inputStream = name;
	}

	void setOutputStream(string name) {
		this->outputStream = name;
	}

	void setNotDuplicateField(string field) {
		this->notDuplicateField = field;
	}

	void addNotUnusualField(string field) {
		this->notUnusualFieldList.push_back(field);
	}
};