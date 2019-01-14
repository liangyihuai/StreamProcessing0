#pragma once

#include "CQSpec.h"
#include "SpecParser.h"


class CQSpecParser: public SpecParser {
public:

	static list<CQSpec*> parseAllCQSpec(const list<string> allCQSpecs) {
		list<CQSpec*> result;
		list<string> cqSpec;
		for (string line : allCQSpecs) {
			line = Utils::toLower(Utils::trim(line));
			if (line.size() == 0 || line[0] == '#') continue;

			cqSpec.push_back(line);
			if (line.find("then") == 0) {
				CQSpec* spec = parseOneCQSpec(cqSpec);
				result.push_back(spec);
				cqSpec.clear();
			}
		}
		return result;
	}

	/*
	If distance < 20
	From airplane
	Window type=, len=, sliding=
	Then WideAreaDefenceTarget
	*/
	static CQSpec* parseOneCQSpec(list<string> oneCQSpec) {
		CQSpec * result = nullptr;
		Predicate* condition = nullptr;
		string inputStream;
		string streamSource;

		for (string s : oneCQSpec) {
			if (s.size() == 0) continue;
			size_t index = s.find_first_of(" ", 0);
			if (index < 0) {
				LOG(ERROR) << "no clause";
				throw runtime_error("");
			}

			string clause = s.substr(0, index);
			string value = s.substr(index + 1, s.size() - index - 1);
			Utils::deleteAllMark(value, " ");

			if ("if" == clause) {
				condition = parseMultiExpression(value);
			}
			else if ("from" == clause) {
				inputStream = value;
			}
			else if ("window" == clause) {

			}
			else if ("then" == clause) {
				streamSource = value;
				result = new CQSpec();
				result->setInputStream(inputStream);
				result->setOutputStream(streamSource);
				result->setPredicate(condition);
				return result;
			}
			else {
				LOG(ERROR) << "undefined CQ spec term";
				throw "undefined CQ spec term";
			}
		}
		return result;
	}
};