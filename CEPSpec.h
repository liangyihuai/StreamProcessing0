#pragma once

#include "Spec.h"
#include <vector>
#include "WindowBase.h"
#include "CEPProcess.h"

class CEPSpec : public Spec {
private:
	vector<string> inputStreams;
	vector<string> outputStreams;

	vector<Predicate*> predicateVec;
	vector<string> precessedStreamVec;

	WindowBase * win;

public:
	CEPProcess * instance() {
		CEPProcess* cep = new CEPProcess();
		for (string os : outputStreams) {
			cep->addOutputStream(os);
		}
	
		for (int i = 0; i < inputStreams.size(); i++) {
			cep->addPredicate(predicateVec[i], inputStreams[i]);
		}

		//cep->setWindow(win);
		return cep;
	}



	void addOutputStream(string name) {
		outputStreams.push_back(name);
	}

	void addPredicate(Predicate * pre, string stream) {
		predicateVec.push_back(pre);
		inputStreams.push_back(stream);
	}


};