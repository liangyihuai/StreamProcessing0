#include "stdafx.h"
#include "CEPSpec.h"
#include "CEPPrintResultListener.h"

CEPSpec::CEPSpec() {
	win = nullptr;
	sinkType = SinkType::PRINT_OUT;//the default sink type is print out.
}

CEPProcess * CEPSpec::instance() {
	CEPProcess* cep = new CEPProcess(inputStreams , outputStreamName);

	for (int i = 0; i < inputStreams.size(); i++) {
		cep->addCondition(predicateVec[i], inputStreams[i]);
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

void CEPSpec::setOutputStreamName(string name) {
	outputStreamName = name;
}

void CEPSpec::addPredicate(ExistOp * pre, string stream) {
	predicateVec.push_back(pre);
	inputStreams.push_back(stream);
}