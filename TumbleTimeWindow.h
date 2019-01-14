#pragma once

#include "WindowBase.h"


class TumbleTimeWindow : public WindowBase{
private:
	int timeLen;
	//int timeSliding;
	QueueReader* reader = nullptr;

	long long previousSlidingTime = -1;
public:
	TumbleTimeWindow(int len);
	//---------------------------------------------
	//implementation
	//----------------------------------------
	unsigned getLen() const;
	unsigned int getSliding() const;
	bool slidingNow();
	bool isEmpty();
	EventPtr next();
	WindowBase * clone();
	QueueReader* getReader();
	void setReader(QueueReader* reader);
	
	~TumbleTimeWindow();
};

