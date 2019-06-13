#pragma once

#include "Spec.h"
#include "../expression/Predicate.h"
#include "../op/win/Window.h"
#include "../util/Utils.h"
#include "../execution/CQProcess.h"

class CQSpec : public Spec{
private:
	vector<string> inputStreams;
	string outputStream;
	Predicate * predicate;
	int winLen = -1;
	int winSliding = -1;
public:
	//An new attr has a value from spec. For example, "THEN SevereThreat, threatLevel=severe"
	//But some do not have. For example, "THEN SevereThreat, count(*)"
	vector<string> newAttrNames;
	vector<string> newAttrValues;

	CQProcess * instance();

	void setInputStreams(vector<string> names);

	void setOutputStream(string name);

	void setPredicate(Predicate * pre);

	void setWindowlen(int len);

	void setWindowSliding(int sliding);
};