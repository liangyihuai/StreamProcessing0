#include "stdafx.h"
#include "CEPSpec.h"
#include "CEPPrintResultListener.h"

CEPSpec::CEPSpec() {
	win = nullptr;
	sinkType = SinkType::PRINT_OUT;//the default sink type is print out.
}

CEPProcess * CEPSpec::instance() {
	CEPProcess* cep = new CEPProcess();
	for (string os : outputStreams) {
		cep->addOutputStream(os);
	}

	for (int i = 0; i < inputStreams.size(); i++) {
		cep->addPredicate(predicateVec[i], inputStreams[i]);
	}

	//cep->setWindow(win);

	if (sinkType == SinkType::PRINT_OUT) {
		cep->setResultListener(new CEPPrintResultListener());
	}
	else if (sinkType == SinkType::SAVE_FILE) {
		LOG(ERROR) << "have not implemented file saving";
		throw runtime_error("");
	}

	return cep;
}



void CEPSpec::addOutputStream(string name) {
	outputStreams.push_back(name);
}

void CEPSpec::addPredicate(Predicate * pre, string stream) {
	predicateVec.push_back(pre);
	inputStreams.push_back(stream);
}