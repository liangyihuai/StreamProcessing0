#pragma once
#include "WindowBase.h"

class SlidingWindowOfCount: public WindowBase {
	unsigned int len;
	unsigned int sliding;
public:
	SlidingWindowOfCount(unsigned int len, unsigned int sliding):len(len), sliding(sliding){}

	unsigned int getLen() const {
		return len;
	}

	unsigned int getSliding() const {
		return sliding;
	}
};
