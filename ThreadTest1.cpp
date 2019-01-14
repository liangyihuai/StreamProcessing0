#include "stdafx.h"
#include <thread>
#include <iostream>

class ThreadWrapper {
public:
	void member1() {
		std::cout << "i am member1" << std::endl;
	}
	void member2(const char *arg1, unsigned arg2) {
		std::cout << "i am member2 and my first arg is (" << arg1 << ") and second arg is (" << arg2 << ")" << std::endl;
	}

	std::thread member1Thread() {
		return std::thread(&ThreadWrapper::member1, this);
	}
	std::thread member2Thread(const char *arg1, unsigned arg2) {
		return std::thread(&ThreadWrapper::member2, this, arg1, arg2);
	}
};

int main0() {
	ThreadWrapper *w = new ThreadWrapper();
	std::thread tw1 = w->member1Thread();
	tw1.join();
	w->member2Thread("hello", 100).detach();

	system("pause");
	return 0;
}