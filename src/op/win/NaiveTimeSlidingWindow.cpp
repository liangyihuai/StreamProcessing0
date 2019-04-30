#include "../../stdafx.h"
#include "NaiveTimeSlidingWindow.h"


NaiveTimeSlidingWindow::NaiveTimeSlidingWindow(int timeLen) {
	this->timeWinLen = timeLen;
}


void NaiveTimeSlidingWindow::reevaluate(double& result) {
	refresh();

	ResultPtr r = op->resultMultEvents(&eventQueue, true);
	result = r->getResultDouble();
}

void NaiveTimeSlidingWindow::reevaluate(long& result) {
	refresh();

	ResultPtr r = op->resultMultEvents(&eventQueue, true);
	result = r->getResultLong();
}

void NaiveTimeSlidingWindow::reevaluate(bool& result) {
	refresh();

	ResultPtr r = op->resultMultEvents(&eventQueue, true);
	result = r->getResultBool();
}


void NaiveTimeSlidingWindow::refresh() {
	long long curr = Utils::getTime();
	while (!eventQueue.empty() && eventQueue.front()->getTime() + timeWinLen < curr) {
		eventQueue.pop_front();
	}
}


bool NaiveTimeSlidingWindow::push_back(EventPtr e) {
	if (eventQueue.size() > MAX_WINDOW_SIZE) {
		std::cout << "the window is full. operator name: ExistOP, stream name: ";
		return false;
	}

	if (e == nullptr) {
		throw "the parameter is empty.";
	}

	eventQueue.push_back(e);
	return true;
}


EventPtr NaiveTimeSlidingWindow::front() {
	return eventQueue.front();
}


bool NaiveTimeSlidingWindow::empty() {
	return eventQueue.empty();
}


int NaiveTimeSlidingWindow::size() {
	return eventQueue.size();
}


Window* NaiveTimeSlidingWindow::clone() {
	throw runtime_error("not implemented");
}




void NaiveTimeSlidingWindow::setStatefulOperator(StatefulOperator* opera) {
	this->op = opera;
}