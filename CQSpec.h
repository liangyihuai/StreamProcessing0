#pragma once

#include "Spec.h"
#include "Predicate.h"
#include "Window.h"
#include "Utils.h"
#include "CQProcess.h"
#include "CQStoreResultListener.h"

class CQSpec : public Spec{
private:
	string inputStream;
	string outputStream;
	Predicate * predicate;
	string windowType;
	int winLen;
	int winSliding;
public:
	CQProcess * instance();

	void setInputStream(string name);

	void setOutputStream(string name);

	void setPredicate(Predicate * pre);

	void setWindowType(string type);

	void setWindowlen(int len);

	void setWindowSliding(int sliding);
};