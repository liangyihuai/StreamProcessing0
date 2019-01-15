#pragma once

#include "Spec.h"
#include <vector>
#include "WindowBase.h"
#include "CEPProcess.h"
#include "SinkType.h"


class CEPSpec : public Spec {
private:
	vector<string> inputStreams;
	vector<string> outputStreams;

	vector<Predicate*> predicateVec;
	vector<string> precessedStreamVec;

	WindowBase * win;

	SinkType sinkType;

public:
	CEPSpec();

	CEPProcess * instance();

	void addOutputStream(string name);

	void addPredicate(Predicate * pre, string stream);
};