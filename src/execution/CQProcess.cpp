//
// Created by USER on 12/5/2018.
//
#include "../stdafx.h"
#include "CQProcess.h"
#include "../cqindex/ProcessRegisterForCQIndex.h"
#include "../op/win/Window.h"

CQProcess::CQProcess(vector<string> inputStreamNames, string outputStreamName) {
	this->outputStreamName = outputStreamName;
	this->inputStreamNames = inputStreamNames;
	for (int i = 0; i < inputStreamNames.size(); i++) {
		this->inputQueues.push_back(new queue<EventPtr>());
	}
}

void CQProcess::addOutputQueue(queue<EventPtr> *inputQueueOfDownstreamProcessUnit, string outputNameOfDownstreamProcessUnit) {
	inputQueueSetOfDownstreamProcessUnit.push_back(inputQueueOfDownstreamProcessUnit);
	outputNameSetOfDownstreamProcessUnit.push_back(outputNameOfDownstreamProcessUnit);
}

bool CQProcess::process(int timeSlice){
	Window* win = nullptr;

	for (int i = 0; i < inputQueues.size(); i++) {
		int timeSlice_i = timeSlice;
		queue<EventPtr>* q = inputQueues[i];
		while (!q->empty() && timeSlice_i > 0) {//current input queue is not empty.
			EventPtr currEvent = q->front();//get the oldest event.
			if (predicates[i]->check(currEvent)) {//check the query condition.
				if (windowList.size() == 0 || (inputQueues.size() == 1 && operatorNames.size() == 0)) {
					for (queue<EventPtr>* outputQueue : inputQueueSetOfDownstreamProcessUnit) {
						outputQueue->push(currEvent);
						cout << "CQ:" << outputStreamName << "; " << *currEvent << endl;
					}
				}else {
					try {
						windowList[i]->push_back(currEvent);
					}
					catch (std::logic_error& e) {
						std::cout << "[exception caught]\n";
					}
				}
			}
			q->pop();
			timeSlice_i--;

			triggerResult();
		}
	}//end for inputQueues

	return true;
}


void CQProcess::triggerResult() {
	//check output trigger
	if (!ExecuteScheduler::cq_pq.empty()) {
		try {
			std::lock_guard<mutex> lg(ExecuteScheduler::mutexOfCQPriorityQueue);//mutex lock for variable "cq_pq".
			//time to output result.
			while (ExecuteScheduler::cq_pq.top()->triggerTime <= Utils::getTime()) {
				Process_TriggerTime* ptt = ExecuteScheduler::cq_pq.top();
				//check whether it meets the output conditions
				bool meetQueryCondition = true;
				if (inputQueues.size() > 1) {//if more than one input stream
					for (int i = 0; i < predicates.size(); i++) {
						bool checkResult = windowList[i]->checkAllEvents(*predicates[i]);
						if (!checkResult) {//all input stream should meet the query condition.
							meetQueryCondition = false;
							break;
						}
					}
				}
				if (meetQueryCondition) {
					EventPtr currEvent(windowList[0]->front()->clone());//clone the event
					for (int i = 0; i < ptt->p->operatorNames.size(); i++) {
						string operatorName = ptt->p->operatorNames[i];
						string operatorParam = ptt->p->operatorParamaters[i];

						if (dynamic_cast<StatefulOperator*>(ptt->p) != nullptr) {
							//如果Then中存在算子，比如count. Then AirplaneCountSevereThreat, Count()
							if (operatorName == "count") {//for count operator

								long countResult = 0;
								windowList[0]->reevaluate(countResult);//目前只考虑在有operator时只有一个window

								currEvent->addAttr(operatorName, countResult);
								stringstream ss;
								ss << Utils::getTime();//current timestamp
								currEvent->addAttr("time", ss.str());
							}
							else if (operatorName == "max"
								|| operatorName == "min"
								|| operatorName == "sum"
								|| operatorName == "ave"
								|| operatorName == "average"
								|| operatorName == "distance") {
								//...
							}
							else {
								throw "no such an operator.";
							}
						}//end if stateful operators
					}

					//如果Then下存在新的属性，比如threatLevel. THEN SevereThreat, threatLevel=severe
					for (int i = 0; i < ptt->p->newAttrNames.size(); i++) {
						string attrName = ptt->p->newAttrNames[i];
						string attrValue = ptt->p->newAttrValues[i];

						if (attrValue.length() > 0) {
							//add new attrs and values to the oldest event in the window
							currEvent->addAttr(attrName, attrValue);//目前只考虑在有新attr时只有一个window
						}
						else {
							cout << "This new attr is not an operator and its value is null." << endl;
							throw "";
						}
					}//end for new attributes
					//如果newAttrNames和operatorNames都为空，就time和output stream name
					if (operatorNames.size() == 0 && newAttrNames.size() == 0) {
						Event* e = new Event(Utils::id++, Utils::getTime());
						e->addAttr("name", this->outputStreamName);
						EventPtr ep(e);
						for (queue<EventPtr>* outputQueue : inputQueueSetOfDownstreamProcessUnit) {
							outputQueue->push(ep);
							cout << "CQ:" << outputStreamName << "; " << *ep << endl;
						}
					}
					else {
						currEvent->addAttr("name", this->outputStreamName);
						for (queue<EventPtr>* outputQueue : inputQueueSetOfDownstreamProcessUnit) {
							outputQueue->push(currEvent);
							cout << "CQ:" << outputStreamName << "; " << *currEvent << endl;
						}
					}
				}
				ExecuteScheduler::cq_pq.pop();
				ptt->triggerTime = Utils::getTime() + ptt->triggerLen;
				ExecuteScheduler::cq_pq.push(ptt);
			}//end while to trigger results
		}
		catch (std::logic_error& e) {
			std::cout << "[exception caught]\n";
		}
	}//end if priority queue is not empty
}

vector<string> CQProcess::getInputStreamNames() {
	return inputStreamNames;
}

vector<queue<EventPtr>*> CQProcess::getInputQueues() {
	return inputQueues;
}

string CQProcess::getOutputStreamName() {
	return outputStreamName;
}


void CQProcess::addPredicate(Predicate * pre) {
	this->predicates.push_back(pre);
}

void CQProcess::setPredicates(vector<Predicate*> preList) {
	this->predicates = preList;
}

void CQProcess::setInputStreamNames(vector<string> names) {
	this->inputStreamNames = names;
}

void CQProcess::setOutputStreamName(string stream){
    this->outputStreamName = stream;
}

vector<Predicate*> CQProcess::getPredicates() {
	return this->predicates;
}

set<string> CQProcess::getConnectedOutputNameSet() {
	set<string> nameSet;
	for (string name : outputNameSetOfDownstreamProcessUnit) {
		nameSet.insert(name);
	}
	return nameSet;
}

void CQProcess::addEventToQueue(EventPtr e, queue<EventPtr>& q) {
	q.push(e);
}

bool CQProcess::removeOutputQueueAndNameFromA(string outputNameOfProcessUnitB) {
	for (int i = 0; i < outputNameSetOfDownstreamProcessUnit.size(); i++) {
		if (outputNameSetOfDownstreamProcessUnit[i] == outputNameOfProcessUnitB) {//exists
			delete inputQueueSetOfDownstreamProcessUnit[i];

			int j = i + 1;
			for (; j < outputNameSetOfDownstreamProcessUnit.size(); j++) {//move reaward one step.
				outputNameSetOfDownstreamProcessUnit[j - 1] = outputNameSetOfDownstreamProcessUnit[j];
				inputQueueSetOfDownstreamProcessUnit[j - 1] = inputQueueSetOfDownstreamProcessUnit[j];
			}
			outputNameSetOfDownstreamProcessUnit.pop_back();
			inputQueueSetOfDownstreamProcessUnit.pop_back();
			return true;
		}
	}
	return false;
}


bool CQProcess::removeAllDownStreamQueuesAndNames() {
	inputQueueSetOfDownstreamProcessUnit.clear();
	outputNameSetOfDownstreamProcessUnit.clear();
	return true;
}

CQProcess::~CQProcess(){
	for (Predicate* pre : predicates) {
		delete pre;
		pre = nullptr;
	}
	
}

void CQProcess::setWindows(vector<Window*> winlist) {
	this->windowList = winlist;
}