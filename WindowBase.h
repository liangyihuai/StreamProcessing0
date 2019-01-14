#pragma once

#include "QueueReader.h"

class WindowBase {
public:
	virtual unsigned getLen() const = 0;
	virtual unsigned int getSliding() const = 0;
	virtual bool slidingNow() = 0;
	virtual bool isEmpty() = 0;
	virtual EventPtr next() = 0;
	virtual WindowBase * clone() = 0;
	virtual QueueReader* getReader() = 0;
	virtual void setReader(QueueReader* reader) = 0;
};