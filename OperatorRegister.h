#pragma once

#include "stdafx.h"
#include "Operator.h"
#include "DistanceOp.h"
#include "Count.h"
#include "Sum.h"
#include "Utils.h"
#include "Filter.h"
#include "Max.h"
#include "Min.h"
#include "Average.h"
#include "ExistOp.h"

class OperatorRegister {
	const static string opNames[8];
public:
	static bool isOperator(string name);

	static Operator * getInstance(string opName, vector<string> params);
};

