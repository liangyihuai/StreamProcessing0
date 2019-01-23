#pragma once

#include "stdafx.h"

#include "Condition.h"
#include "CQSpec.h"
#include "EventFilterSpec.h"
#include "EventCapture.h"
#include "CEPSpec.h"
#include "OperatorRegister.h"
#include "BoolOpPredicate.h"
#include "GreatThanOpPreDouble.h"
#include "LessThanOpPreDouble.h"
#include "Predicate.h"

//the base class for parsing specs. 
class SpecParser {
public:

	//currently, assume only & conjunction
	static Predicate * parseMultiExpression(string expStr);

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