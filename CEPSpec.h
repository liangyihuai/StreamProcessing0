#pragma once

#include "Spec.h"
#include <vector>
#include "WindowBase.h"
#include "CEPProcess.h"
#include "SinkType.h"


class CEPSpec : public Spec {
private:
	vector<string> inputStreams;
	string outputStreamName;

	//vector<Predicate*> predicateVec;
	vector<ExistOp*> predicateVec;
	vector<string> precessedStreamVec;

	WindowBase * win;

	SinkType sinkType;

public:
	CEPSpec();

	CEPProcess * instance();

	void setOutputStreamName(string name);

	void addPredicate(ExistOp * pre, string stream);
};