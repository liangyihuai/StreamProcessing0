#include "../stdafx.h"
#include "SpecParser.h"

Predicate * SpecParser::parseMultiExpression(string expStr) {
	And * andPredicate = nullptr;
	vector<string> expressionList = Utils::split(expStr, "&");
	if (expressionList.size() > 0) {
		andPredicate = new And();
		for (string expression : expressionList) {
			string stream;
			string fieldName;
			string mid;
			string right;
			splitExpression(expression, stream, fieldName, mid, right);
			int index1 = fieldName.find("(");
			int index2 = fieldName.find(")");
			if ((index1 > -1 && index2 > -1)
				|| OperatorRegister::isOperator(fieldName)) {
				andPredicate->addChild(parseExpressionWithOperator(expression));
			}
			else {
				andPredicate->addChild(parseValueExpression(fieldName, mid, right));
			}
		}
	}
	return andPredicate;
}

//format is: "streamName.field mid right", for example: "plane.speed > 12"
//It could be "streamName.operatorName() > 12", or
//"operatorName(streamName.fieldName) > 12"
bool SpecParser::splitExpression(const string expression, string& stream, string & fieldName, string &mid, string & right) {
	int index = -1;
	string left;
	if ((index = expression.find(">=")) != -1) {
		left = expression.substr(0, index);
		right = expression.substr(index + 2, expression.size() - index - 2);
		mid = ">=";
	}
	else if ((index = expression.find(">")) != -1) {
		left = expression.substr(0, index);
		right = expression.substr(index + 1, expression.size() - index - 1);
		mid = ">";
	}
	else if ((index = expression.find("<=")) != -1) {
		left = expression.substr(0, index);
		right = expression.substr(index + 2, expression.size() - index - 2);
		mid = "<=";
	}
	else if ((index = expression.find("<")) != -1) {
		left = expression.substr(0, index);
		right = expression.substr(index + 1, expression.size() - index - 1);
		mid = "<";
	}
	else if ((index = expression.find("==")) != -1) {
		left = expression.substr(0, index);
		right = expression.substr(index + 2, expression.size() - index - 2);
		mid = "==";
	}
	else if ((index = expression.find("=")) != -1) {
		left = expression.substr(0, index);
		right = expression.substr(index + 1, expression.size() - index - 1);
		mid = "=";
	}
	else {
		std::cout << "no expression predicate";
		throw runtime_error("");
	}
	if ((index = left.find(".")) != -1) {

		int index2 = left.find("(");
		if (index2 == -1) {
			stream = left.substr(0, index);
			fieldName = left.substr(index + 1, left.size() - index - 1);
		}
		else if (index < index2) {
			stream = left.substr(0, index);
			fieldName = left.substr(index + 1, left.size() - index - 1);
		}
		else {
			fieldName = left;
		}

	}
	else {
		fieldName = left;
	}
	return true;
}

Predicate * SpecParser::parseValueExpression(string name, string mid, string value) {
	int index = -1;
	if (mid == "==" || mid == "=") {
		return new EqualString(value, name);
	}
	else {
		stringstream ss;
		float f = 0.0;
		ss << value;
		ss >> f;
		if (mid == ">=") {
			return new GreaterThanFloat(f, name);
		}
		else if (mid == ">") {
			return new GreaterThanFloat(f, name);
		}
		else if (mid == "<=") {
			return new LessThanFloat(f, name);
		}
		else if (mid == "<") {
			return new LessThanFloat(f, name);
		}
	}
	std::cout << "undefined expression";
	throw "";
}

//parse the expression with operator
//1. parse and generate operator
//2. parse and generate predicate object
Predicate * SpecParser::parseExpressionWithOperator(string expression) {

	vector<string> parameters;

	string stream;
	string opName;
	string mid;
	string right;
	splitExpression(expression, stream, opName, mid, right);

	int index1 = opName.find("(");

	if (index1 >= 0) {
		string tempName = opName.substr(0, index1);
		int index2 = opName.find(")");
		string paramsStr = opName.substr(index1 + 1, index2 - index1 - 1);
		vector<string> params = Utils::split(paramsStr, ",");

		for (string param : params) {
			parameters.push_back(param);
		}
		opName = tempName;
	}
	Operator * op = OperatorRegister::getInstance(opName, parameters);
	//Operator * doubleOp = dynamic_cast<Operator<double>*>(op);
	string value = right;

	stringstream ss;
	float f = 0.0;
	ss << value;
	ss >> f;
	if (mid == ">=") {
		return new GreatThanOpPreDouble(op, f);
	}
	else if (mid == ">") {
		return new GreatThanOpPreDouble(op, f);
	}
	else if (mid == "<=") {
		return new LessThanOpPreDouble(op, f);
	}
	else if (mid == "<") {
		return new LessThanOpPreDouble(op, f);
	}
	std::cout << "undefined expression";
	throw "undefined expression";
}