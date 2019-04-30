#pragma once

#include "../../common/Event.h"
#include <vector>


class Result {
public:
	virtual long getResultLong() {
		cout << "not implemented" << endl;
		throw runtime_error("");
	};
	virtual double getResultDouble() {
		cout << "not implemented" << endl;
		throw runtime_error("");
	};
	virtual bool getResultBool() {
		cout << "not implemented" << endl;
		throw runtime_error("");
	};

	virtual EventPtr getResultEvent() {
		cout << "not implemented" << endl;
		throw runtime_error("");
	};

	virtual vector<EventPtr> getResultEventVec() {
		cout << "not implemented" << endl;
		throw runtime_error("");
	}
};

//template<typename T>
//using ResultPtr = std::shared_ptr<Result<T>>;

typedef shared_ptr<Result> ResultPtr;