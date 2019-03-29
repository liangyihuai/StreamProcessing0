#pragma once

#include <queue>
#include "../execution/EventProcess.h"
#include "../execution/Process.h"
#include <unordered_map>
#include "../execution/CEPProcess.h"
#include <set>


class TopoGraph {
public:
	static void addProcessUnitToGraph(Process* pro);
	static void removeProcessFromGraph(string outputStreamName);
	static void setEventFilter(EventProcess* ep);
private:
	static void addProcessUnitToGraph(string inputStreamNameOfB, queue<EventPtr> * inputQueueOfB, string outputNameOfB);

private:
	static EventProcess *eventProcess;
	//output stream name -> process
	static std::unordered_map<string, Process*> processMap;
};
