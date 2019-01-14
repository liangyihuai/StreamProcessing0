#pragma once
#include "WindowBase.h"

class TumbleCountWindow : public WindowBase{
	unsigned int countLen;//countLen == countSliding
	//unsigned int countSliding;

	int tempCount = 0;//

	QueueReader * reader = nullptr;
public:
	TumbleCountWindow(unsigned int countLen);

	unsigned getLen() const;

	unsigned int getSliding() const;

	//whether slides the window now
	bool slidingNow() {
		bool result = false;
		if (tempCount >= countLen) {
			result = true;
		}
		tempCount = 0;
		return result;
	}

	//whether the window is empty or not.
	bool isEmpty() {
		if (!reader) {
			LOG(ERROR) << "reader null pointer";
			throw runtime_error("reader null pointer");
		}
		return reader->isEmpty();
	}

	EventPtr next() {
		if (isEmpty()) {
			LOG(ERROR) << "the window is empty";
			throw runtime_error("");
		}

		return reader->dequeue();
	}

	WindowBase * clone() {
		TumbleCountWindow * win = new TumbleCountWindow(countLen);
		win->setReader(reader);
		return win;
	}

	QueueReader* getReader() {
		return this->reader;
	}

	void setReader(QueueReader* reader) {
		this->reader = reader;
	}


	~TumbleCountWindow();
};

