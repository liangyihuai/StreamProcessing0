#include "../stdafx.h"
#include "OperatorRegister.h"

const string OperatorRegister::opNames[8] = { "count", "avg", "average", "sum", "distance", "max", "min", "withinarea" };

bool OperatorRegister::isOperator(string name) {
	for (string op : opNames) {
		if (op == name) return true;
	}
	return false;
}

Operator<void> * OperatorRegister::getInstance(string opName, vector<string> params) {
	if (!isOperator(opName)) return nullptr;

	if (opName == "distance") {
		float f1 = 0;
		float f2 = 0;
		string lon = "lon";
		string lat = "lat";
		if (params.size() == 2) {
			stringstream ss;
			ss << params[0];
			ss >> f1;
			ss.clear();
			ss << params[1];
			ss >> f2;
			return dynamic_cast<Operator<void>*>(new DistanceOp(lon, lat, f1, f2));
		}
		else if (params.size() == 4) {
			stringstream ss;
			ss << params[2];
			ss >> f1;
			ss.clear();
			ss << params[3];
			ss >> f2;
			return dynamic_cast<Operator<void>*>(new DistanceOp(params[0], params[1], f1, f2));
		}
		else {
			std::cout << "illegal parameters for operator distance()";
			throw runtime_error("");
		}
	}
	else if ("count" == opName) {
		return dynamic_cast<Operator<void>*>(new Count());
	}
	else if ("sum" == opName) {
		return dynamic_cast<Operator<void>*>(new Sum(params[0]));
	}
	else if ("max" == opName) {
		return dynamic_cast<Operator<void>*>(new Max(params[0]));
	}
	else if ("min" == opName) {
		return dynamic_cast<Operator<void>*>(new Min(params[0]));
	}
	else if ("ave" == opName || "average" == opName) {
		return dynamic_cast<Operator<void>*>(new Average(params[0]));
	}
	else if ("exist" == opName) {
		return dynamic_cast<Operator<void>*>(new ExistOp(params[0]));
	}
	else {
		std::cout << "undefined operator! the opName is " << opName;
		throw "";
	}
}