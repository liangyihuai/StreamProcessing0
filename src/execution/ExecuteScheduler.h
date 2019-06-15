#pragma once

#include <unordered_map>
#include "EventProcess.h"
#include "EventCapture.h"
#include "CQProcess.h"
#include "CEPProcess.h"
#include "Process.h"
#include "TopoGraph.h"
#include "ProcessRegister.h"
#include <queue>

//��Process�������������Ľ������ʱ���������
struct Process_TriggerTime {
	Process* process = nullptr;
	long long triggerTime = -1; // current time plus triggerLen;
	int triggerLen = -1; //time length to trigger, for example 1000ms

	Process_TriggerTime() {}

	Process_TriggerTime(Process* p, int triggerLen) {
		this->process = p;
		this->triggerLen = triggerLen;
	}

	~Process_TriggerTime() {
	}
};

struct cmp {
	bool operator()(Process_TriggerTime* a, Process_TriggerTime* b) {
		return a->triggerTime > b->triggerTime;
	}
};

/*
ά��һ��������в�Ϊ�յ�cp���У�ѭ������cp����������е����ݣ�ֱ��cp����Ϊ�ա�
1. ��������в�Ϊ�յ�ʱ�򣬽���Ӧ�Ķ��м���cp������.
2. ���ϴ�cp����ͷ������һ��cp������cp���������timeSlice�����ݻ��߶���Ϊ�ա����������timeSlice������֮�󣬸ö��в�Ϊ�գ�
�ͽ�����ӵ�cp���е�β���������cp�ж��������У�ֻҪ��һ������Ϊ�գ��Ͳ�����cp����cp�����С�
*/
class ExecuteScheduler {
	friend class CQProcess;
	friend class CEPProcess;
public:
	static void initialize();
	static void runProcessQueue();
	static void buildGraph();
	static void rebuildGraph();

	//�������ȼ�����,��������Ҫ������������process�ڶѵĶ���
	static void buildTriggerTimePriorityQueue();
private:

	//currently it is only for CQProcess.
	static priority_queue<Process_TriggerTime*, vector<Process_TriggerTime*>, cmp > cq_pq;

	static priority_queue<Process_TriggerTime*, vector<Process_TriggerTime*>, cmp > cep_pq;

	static mutex mutexOfCQPriorityQueue;//mutex lock among threads

	static mutex mutexOfCEPPriorityQueue;//mutex lock among threads
};


