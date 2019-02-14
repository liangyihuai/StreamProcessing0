#include "stdafx.h"

#include "ProcessRegisterForCQIndex.h"

vector<Process*> ProcessRegisterForCQIndex::processVector;

Process* ProcessRegisterForCQIndex::getProcess(int index) {
	if (index < 0 || index >= processVector.size())
		throw "the parameter of index is out of bound.";

	return processVector[index];
}

list<Process*> ProcessRegisterForCQIndex::getProcess(vector<int64_t> indexes) {
	list<Process*> processList;
	for (int64_t index : indexes) {
		if (index < 0 || index >= processVector.size())
			throw "the parameter of index is out of bound.";

		processList.push_back(processVector[index]);
	}
	return processList;
}

void ProcessRegisterForCQIndex::addProcess(Process* p) {
	processVector.push_back(p);
}

bool ProcessRegisterForCQIndex::deleteProcess(int index) {
	if (index < 0 || index >= processVector.size())
		return false;

	processVector[index] = nullptr;
	return true;
}

bool ProcessRegisterForCQIndex::deleteProcess(Process* pro) {
	for (int i = 0; i < processVector.size(); i++) {
		if (processVector[i] == pro) {
			processVector[i] = nullptr;
			return true;
		}
	}
	return false;
}







