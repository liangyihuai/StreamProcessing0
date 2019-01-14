#include "stdafx.h"
#include "TumbleTimeWindow.h"


TumbleTimeWindow::TumbleTimeWindow(int len):timeLen(len){
}

unsigned TumbleTimeWindow::getLen() const {
	return timeLen;
}

unsigned int TumbleTimeWindow::getSliding() const {
	return timeLen;
}

bool TumbleTimeWindow::slidingNow() {
	long long time = Utils::getTime();
	if (previousSlidingTime == -1) {
		previousSlidingTime = time;
		return true;
	}
	else if (previousSlidingTime < (time - timeLen)) {
		previousSlidingTime = time;
		return true;
	}
	else return false;
}

bool TumbleTimeWindow::isEmpty() {
	if (!reader) {
		LOG(ERROR) << "reader null poiter";
		throw runtime_error("");
	}
	return reader->isEmpty();
}

EventPtr TumbleTimeWindow::next() {
	if (isEmpty()) {
		LOG(ERROR) << "the window is empty";
		throw runtime_error("");
	}

	return reader->dequeue();
}

WindowBase * TumbleTimeWindow::clone() {
	TumbleTimeWindow* win = new TumbleTimeWindow(timeLen);
	win->setReader(reader);
	return win;
}

QueueReader* TumbleTimeWindow::getReader() {
	return this->reader;
}

void TumbleTimeWindow::setReader(QueueReader* reader) {
	this->reader = reader;
}

TumbleTimeWindow::~TumbleTimeWindow(){
	delete reader;
	reader = nullptr;
}
