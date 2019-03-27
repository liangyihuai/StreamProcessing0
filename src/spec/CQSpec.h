#pragma once

#include "Spec.h"
#include "../expression/Predicate.h"
#include "../execution/win/Window.h"
#include "../util/Utils.h"
#include "../execution/CQProcess.h"
#include "../execution/result/CQStoreResultListener.h"

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