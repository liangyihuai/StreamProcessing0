#pragma once

#include "Window.h"
#include <list>
#include "../../common/Event.h"
#include "../../op/inter/StatefulOperator.h"

/*
the type of template T indicates the result's of stateful operator. 
*/
class NaiveTimeSlidingWindow :public Window {
public:
	NaiveTimeSlidingWindow(int timeLen=1000);

	void refresh() override;
	void reevaluate(double& result)override;
	void reevaluate(long& result)override;
	void reevaluate(bool& result)override;
	bool push_back(EventPtr e)override;
	EventPtr front()override;
	bool empty()override;
	int size()override;
	Window* clone()override;

	void setStatefulOperator(StatefulOperator* opera) override;
private:
	list<EventPtr> eventQueue;
	StatefulOperator* op = nullptr;

	//max size of this window
	int MAX_WINDOW_SIZE = 10000;

	int timeWinLen;
};

