//
// Created by USER on 12/6/2018.
//

#ifndef CONTINUOUSPROCESSING_EXISTOP_H
#define CONTINUOUSPROCESSING_EXISTOP_H

#include "inter/Operator.h"
#include "../util/Utils.h"
#include <list>
#include "../execution/result/BoolResult.h"

namespace exist_op {
	class TimeSlidingWindow{
	public:
		void setTimeLen(int _timeWinLen) {
			this->timeWinLen = _timeWinLen;
		}

		//evict time out events
		void refresh() {
			long long curr = Utils::getTime();
			while (!window.empty() && !window.front()->getTime() + timeWinLen < curr) {
				window.pop_front();
			}
		}

		bool push_back(EventPtr e) {
			if (window.size() > MAX_WINDOW_SIZE) {
				std::cout << "the window is full. operator name: ExistOP, stream name: ";
				return false;
			}

			if (e == nullptr) {
				throw "the parameter is empty.";
			}

			window.push_back(e);
			return true;
		}

		EventPtr front() {
			return window.front();
		}

		bool empty() {
			return window.empty();
		}

	private:
		list<EventPtr> window;

		//max size of this window
		int MAX_WINDOW_SIZE = 10000;

		int timeWinLen;
	};
};

class ExistOp:public Operator<bool>{

public:
	ExistOp(string _streamName, int _timeWinLen=1000);

	//insert an event to the window. If the size of
	//the window is greater than max, return false;
	bool digestEvent(EventPtr e);

	//this is overrided function. to get rusults. In this class, the parameter is nullptr.
	ResultPtr<bool> result(EventPtr event);

private:
	string streamName;

	exist_op::TimeSlidingWindow window;
};


#endif //CONTINUOUSPROCESSING_EXISTOP_H
