#pragma once

#include "Window.h"
#include <list>
#include "../../common/Event.h"
#include "../../op/inter/StatefulOperator.h"

template <typename T>
class NaiveTimeSlidingWindow :public Window<T> {
public:
	void refresh() override;
	void reevaluate(T& result)override;
	bool push_back(EventPtr e)override;
	EventPtr front()override;
	bool empty()override;
	int size()override;
	Window* clone()override;

	void setTargetAttr(string attr);
	void setStatefulOperator(StatefulOperator<T>* opera) override;
private:
	list<EventPtr> eventQueue;
	StatefulOperator<T>* op = nullptr;

	//max size of this window
	int MAX_WINDOW_SIZE = 10000;

	int timeWinLen;
};

template <typename T>
void NaiveTimeSlidingWindow<T>::reevaluate(T& result) {
	ResultPtr<T> r = op->resultMultEvents(&eventQueue, true);
	result = r->getResult();
}

template <typename T>
void NaiveTimeSlidingWindow<T>::refresh() {
	long long curr = Utils::getTime();
	while (!eventQueue.empty() && !eventQueue.front()->getTime() + timeWinLen < curr) {
		eventQueue.pop_front();
	}
}

template <typename T>
bool NaiveTimeSlidingWindow<T>::push_back(EventPtr e) {
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

template <typename T>
EventPtr NaiveTimeSlidingWindow<T>::front() {
	return eventQueue.front();
}

template <typename T>
bool NaiveTimeSlidingWindow<T>::empty() {
	return eventQueue.empty();
}

template <typename T>
int NaiveTimeSlidingWindow<T>::size() {
	return eventQueue.size();
}

template <typename T>
Window<T>* NaiveTimeSlidingWindow<T>::clone() {
	throw runtime_error("not implemented");
}

template <typename T>
void NaiveTimeSlidingWindow<T>::setTargetAttr(string attr) {
	this->targetAttr = attr;
}

template <typename T>
void NaiveTimeSlidingWindow<T>::setStatefulOperator(StatefulOperator<T>* opera) {
	this->op = opera;
}