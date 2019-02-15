#pragma once

#include "string"
#include <vector>
#include "Condition.h"
#include <spatialindex/Point.h>

using namespace std;

namespace cqindex {
	//10 < speed < 20. fieldName=speed, leftValue=10, rightValue=20
	class PredicateDecomposition {
	public:
		std::string fieldName;

		bool existLeftValue = false;
		double leftValue;

		bool existRightValue = false;
		double rightValue;

		std::string strValue;
		bool isStringEqual = false;
		bool isValid = true;
	};
}

class CQIndexUtils {
public:

	static vector<cqindex::PredicateDecomposition> decomposeCondition(Condition * con);

	static vector<cqindex::PredicateDecomposition> sortFields(vector<cqindex::PredicateDecomposition> pdVec);

	static SpatialIndex::Point* transformEventToPoint(EventPtr e);

private:
	static string sortedFieldNames[];

};