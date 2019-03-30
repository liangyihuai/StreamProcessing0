#pragma once

#include <iostream>
#include <vector>
#include <list>
#include "../util/Utils.h"
#include "../spec/EventFilterSpecParser.h"
#include "../spec/EventCaptureSpecParser.h"
#include "../spec/CQSpecParser.h"
#include "../spec/CEPSpecParser.h"
#include "../spec/EventFilterSpec.h"
#include "../spec/EventCaptureSpec.h"
#include"../spec/CQSpec.h"
#include "../spec/CEPSpec.h"
#include "../execution/ProcessRegister.h"
#include "../spec/SpecRegister.h"

using namespace std;

class RuleRegisterUtils {
public:
	//Change CString to string type
	static void specProcessWithCString(CString outputStreamName, CString ruleSpec, string & outputName, string& specLines_out) {
		//parse names 
		outputName = CW2A(outputStreamName.GetString());
		//parse event capture rules
		specLines_out = CW2A(ruleSpec.GetString());
	}

	//CLow case; Change multiple lines of string to list<string>
	static void specPreprocess(string & outputStreamName, const string ruleSpec, list<string>& specLines_out) {
		outputStreamName = Utils::toLower(outputStreamName);
		vector<string> lines = Utils::split(ruleSpec, "\r\n");
		list<string>lines_list;
		for (string line : lines) {
			line = Utils::trim(line);
			lines_list.push_back(line);
		}
		specLines_out = lines_list;
	}

	static void registerEventFilter(string outputStreamName, string ruleSpec) {
		list<string> specLines;
		specPreprocess(outputStreamName, ruleSpec, specLines);

		EventFilterSpec* eventFilterSpec = EventFilterParser::parseOneEventFilterSpec(specLines, outputStreamName);
		EventProcess* ec = eventFilterSpec->instance();
		ProcessRegister::registerEventFilter(ec);
	}

	static void registerEventCapture(string outputStreamName, string ruleSpec) {
		list<string> specLines;
		specPreprocess(outputStreamName, ruleSpec, specLines);
		EventCaptureSpec* spec = EventCaptureSpecParser::parseOneEventCaptureSpec(specLines, outputStreamName);
		EventCapture* ec = spec->instance();
		ProcessRegister::addProcess(ec);
		//store rule specification
		SpecRegister::register_event_capture_rule(outputStreamName, ruleSpec);
	}

	static void registerCQ(string outputStreamName, string ruleSpec) {
		list<string> specLines;
		specPreprocess(outputStreamName, ruleSpec, specLines);
		CQSpec* cqSpec = CQSpecParser::parseOneCQSpec(specLines, outputStreamName);
		CQProcess* cq = cqSpec->instance();
		ProcessRegister::addProcess(cq);
		//store rule specification
		SpecRegister::register_cq_rule(outputStreamName, ruleSpec);
	}

	static void registerCEP(string outputStreamName, string ruleSpec) {
		list<string> specLines;
		specPreprocess(outputStreamName, ruleSpec, specLines);
		CEPSpec* cepSpec = CEPSpecParser::parseOneCEPSpec(specLines, outputStreamName);
		CEPProcess* cep = cepSpec->instance();
		ProcessRegister::addProcess(cep);
		//store rule specifications
		SpecRegister::register_cep_rule(outputStreamName, ruleSpec);
	}

};

