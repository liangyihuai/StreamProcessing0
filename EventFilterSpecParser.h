#pragma once

#include "stdafx.h"

#include "Condition.h"
#include "EventFilterSpec.h"
#include "EventFilterSpec.h"
#include "EventCapture.h"
#include "CEPSpec.h"
#include "OperatorRegister.h"
#include "BoolOpPredicate.h"
#include "GreatThanOpPreDouble.h"
#include "LessThanOpPreDouble.h"
#include "Predicate.h"

/*
//Sample: 
	If not duplicate(id) & not unusual(iff) & not unusual(speed)
	From rawData
	Then targetData
*/
class EventFilterParser {
public:
	static list<EventFilterSpec*> parseAllEventFilterSpec(const list<string> allCQSpecs) {
		list<EventFilterSpec*> result;
		list<string> specStrVec;
		for (string line : allCQSpecs) {
			line = Utils::toLower(Utils::trim(line));
			if (line.size() == 0 || line[0] == '#') continue;

			specStrVec.push_back(line);
			if (line.find("then") == 0) {
				result.push_back(parseOneEventFilterSpec(specStrVec));
				specStrVec.clear();
			}
		}
		return result;
	}

	static EventFilterSpec* parseOneEventFilterSpec(list<string> specStr) {
		EventFilterSpec * eventfilterSpec = new EventFilterSpec();

		for (string s : specStr) {
			if (s.size() == 0) continue;
			size_t index = s.find_first_of(" ", 0);
			if (index < 0) {
				LOG(ERROR) << "no clause";
				throw runtime_error("no clause");
			}

			string clause = s.substr(0, index);
			string value = s.substr(index + 1, s.size() - index - 1);
			//Utils::deleteAllMark(value, " ");

			if ("if" == clause) {
				vector<string> expList = Utils::split(value, "&");
				
				for (string exp : expList) {
					exp = Utils::trim(exp);
					int index = exp.find("(");
					string opName = exp.substr(0, index);
					string field = exp.substr(index+1, exp.size()-index - 2);
					if (opName == "not duplicate") {
						eventfilterSpec->setNotDuplicateField(field);
					}
					else if (opName == "not unusual") {
						eventfilterSpec->addNotUnusualField(field);
					}
				}
			}
			else if ("from" == clause) {
				eventfilterSpec->setInputStream(value);
			}
			else if ("then" == clause) {
				eventfilterSpec->setOutputStream(value);
			}
			else {
				LOG(ERROR) << "undefined CQ spec term";
				throw "undefined CQ spec term";
			}
		}
		return eventfilterSpec;
	}
};
