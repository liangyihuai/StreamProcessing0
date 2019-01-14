//
// Created by USER on 12/6/2018.
//

#include "stdafx.h"

#include <iostream>
#include "CQProcess.h"
#include "RadarEvent.h"
#include "EqualString.h"
#include "EventCapture.h"
#include "CQStoreResultListener.h"
#include "ExecuteScheduler.h"
#include "GreaterThanFloat.h"
#include "And.h"
#include "ExistOp.h"
#include "BoolOpPredicate.h"
#include "CEPPrintResultListener.h"

using namespace std;


int main() {
	LOG(INFO) << "start to test CEP with continuous stream data.";

	list<string> ecSpecStrings = FileReaderUtils::readFile("event_capture_spec2.txt");
	list<EventCaptureSpec*> eventcaptureSpecs = EventCaptureSpecParser::parseAllEventCaptureSpec(ecSpecStrings);
	for (EventCaptureSpec* spec : eventcaptureSpecs) {
		EventCapture* ec = spec->instance();
		ExecuteScheduler::registerEventCapture(ec);
	}

	/*QueueReader ecReader2;
	DerivedEventStore::registerReader("enemytarget", &ecReader2);*/

	list<string> cqSpecStrings = FileReaderUtils::readFile("cq_spec2.txt");
	list<CQSpec*> cqSpecs = CQSpecParser::parseAllCQSpec(cqSpecStrings);
	for (CQSpec* spec : cqSpecs) {
		CQProcess * cq = spec->instance();
		ExecuteScheduler::registerCQProcess(cq);
	}
	/*QueueReader cqReader1;
	DerivedEventStore::registerReader("flyingtarget", &cqReader1);
*/

	/*QueueReader cqReader2;
	DerivedEventStore::registerReader("nearenemytarget", &cqReader2);*/


	list<string> cepSpecStrings = FileReaderUtils::readFile("cep_spec2.txt");
	list<CEPSpec*> cepSpecs = CEPSpecParser::parseAllCEPSpec(cepSpecStrings);
	for (CEPSpec* spec : cepSpecs) {
		CEPProcess* cep = spec->instance();
		cep->setResultListener(new CEPPrintResultListener());
		ExecuteScheduler::registerCEPProcess(cep);
	}
	/*QueueReader cepReader1;
	DerivedEventStore::registerReader("ceptarget1", &cepReader1);*/

	for (int i = 0; i < 1000000; i++) {
		EventPtr e = EventGenerator::generateEvent();
		ExecuteScheduler::run(e);
		ExecuteScheduler::executeCEPProcess();

		/*
		while (!ecReader2.isEmpty()) {
			EventPtr e = ecReader2.dequeue();
			cout << "EventCapture: enemytarget, id=" << e->getId() << ", iff=" << e->getString("iff") << ", speed=" << e->getFloat("speed") << endl;
		}
		while (!cqReader1.isEmpty()) {
			EventPtr e = cqReader1.dequeue();
			cout << "Eventcapture: flyingtarget, id=" << e->getId() << ", iff=" << e->getString("iff") << ", speed=" << e->getFloat("speed") << endl;
		}*/

		/*while (!cqReader2.isEmpty()) {
			EventPtr e = cqReader2.dequeue();
			cout << "Eventcapture: nearEnemyTarget, id=" << e->getId() << ", iff=" << e->getString("iff") << ", speed=" << e->getFloat("speed") << endl;
		}*/
	}
	
	system("pause");
	return 0;
};
