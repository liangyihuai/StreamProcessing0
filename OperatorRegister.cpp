#include "stdafx.h"
#include "OperatorRegister.h"

const string OperatorRegister::opNames[8] = { "count", "avg", "average", "sum", "distance", "max", "min", "withinarea" };

bool OperatorRegister::isOperator(string name) {
	for (string op : opNames) {
		if (op == name) return true;
	}
	return false;
}

Operator * OperatorRegister::getInstance(string opName, vector<string> params) {
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
			return new DistanceOp(lon, lat, f1, f2);
		}
		else if (params.size() == 4) {
			stringstream ss;
			ss << params[2];
			ss >> f1;
			ss.clear();
			ss << params[3];
			ss >> f2;
			return new DistanceOp(params[0], params[1], f1, f2);
		}
		else {
			LOG(ERROR) << "illegal parameters for operator distance()";
			throw runtime_error("");
		}
	}
	else if ("count" == opName) {
		return new Count();
	}
	else if ("sum" == opName) {
		return new Sum(params[0]);
	}
	else if ("max" == opName) {
		return new Max(params[0]);
	}
	else if ("min" == opName) {
		return new Min(params[0]);
	}
	else if ("ave" == opName || "average" == opName) {
		return new Average(params[0]);
	}
	else if ("exist" == opName) {
		return new ExistOp(params[0]);
	}
	else {
		LOG(ERROR) << "undefined operator! the opName is " << opName;
		throw "";
	}
}