#pragma once

#include "SpecParser.h"

#include "Condition.h"

#include "EventFilterSpec.h"
#include "EventCapture.h"
#include "CEPSpec.h"
#include "OperatorRegister.h"
#include "BoolOpPredicate.h"
#include "GreatThanOpPreDouble.h"
#include "LessThanOpPreDouble.h"
#include "Predicate.h"
#include "glog\logging.h"

class CEPSpecParser{

public:

	//static list<CEPSpec*> parseAllCEPSpec(const list<string> allCEPSpecs);

	/*
	If distance < 20
	From airplane
	Window type=, len=, sliding=
	Then WideAreaDefenceTarget
	*/
	static CEPSpec* parseOneCEPSpec(list<string> oneCEPSpec, string outputStreamName);

private:
	//currently, assume only & conjunction
	static void parseMultiExpression(string expStr, CEPSpec *cepSpec);

	//only parsing the operator existOp()
	static void parseExistOpExpression(string expStr, CEPSpec * cepSpec);

	//format is: "streamName.field mid right", for example: "plane.speed > 12"
	//It could be "streamName.operatorName() > 12", or
	//"operatorName(streamName.fieldName) > 12"
	static bool splitExpression(const string expression, string& stream, string & fieldName, string &mid, string & right);

	static Predicate * parseValueExpression(string name, string mid, string value);

	//parse the expression with operator
	//1. parse and generate operator
	//2. parse and generate predicate object
	static Predicate * parseExpressionWithOperator(string expression);
};