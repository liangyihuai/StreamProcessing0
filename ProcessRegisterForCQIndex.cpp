#include "stdafx.h"

#include "ProcessRegisterForCQIndex.h"
#include "CQIndex.h"
#include "RTreeCQIndex.h"

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

int ProcessRegisterForCQIndex::getId(Process* process) {
	for (int i = 0; i < processVector.size(); i++) {
		if (process == processVector[i]) {
			return i;
		}
	}
	return -1;
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


void ProcessRegisterForCQIndex::buildIndexGraph(
			unordered_map<string, Process*> processMap, int minConnection, int dimension_index){
	//----------------------------------
	//find relation among CQProcess
	//----------------------------------
	map<Process*, set<CQProcess*>*> relations;//a process unit can connect to multiple other process units.
	for (auto iter = processMap.begin(); iter != processMap.end(); iter++) {//for each all process
		if (CQProcess* cq = dynamic_cast<CQProcess*>(iter->second)) {//filter CQ process
			vector<string> inputStreamNames = cq->getInputStreamNames();
			for (string s : inputStreamNames) {//for each input stream for current process unit
				Process* cq_in = processMap[s];
				if (relations.find(cq_in) == relations.end())
					relations[cq_in] = new set<CQProcess*>;
				relations[cq_in]->insert(cq);//build the relation
			}
		}
	}
	//--------------------------------
	//build index
	//--------------------------------
	for (auto iter = relations.begin(); iter != relations.end(); iter++) {
		//filter the process units that have enough connection with others.
		if (iter->second->size() >= minConnection) {
			CQIndex* index = new RTreeCQIndex(dimension_index);
			for (CQProcess* cq_index : *(iter->second)) {
				Predicate* predicate = cq_index->getPredicate();
				int regionInIndex = getId(cq_index);
				index->buildIndex(predicate, regionInIndex);
			}
			Process* cq = iter->first;
			indexedProcessSet.insert(cq);//register the indexed process unit.
			processIndexMap[cq] = index;
		}
	}
}




