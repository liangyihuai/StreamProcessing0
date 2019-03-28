#pragma once

#include "../../common/Event.h"
#include <vector>

template <typename T>
class Result {
public:
	virtual T getResult() {
		cout << "not implemented" << endl;
		throw runtime_error("");
	};

	virtual vector<T> getResultVec() {
		cout << "not implemented" << endl;
		throw runtime_error("");
	}
};

template<typename T>
using ResultPtr = std::shared_ptr<Result<T>>;