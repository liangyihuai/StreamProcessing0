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
class Process_TriggerTime {
public:
	Process* p = nullptr;
	long long triggerTime = -1; // current time plus triggerLen;
	int triggerLen = -1; //time length to trigger, for example 1000ms

	Process_TriggerTime() {}

	Process_TriggerTime(Process* p, int triggerLen) {
		this->p = p;
		this->triggerLen = triggerLen;
	}

	friend bool operator < (Process_TriggerTime& a, Process_TriggerTime& b) {//����trueʱ��˵��a�����ȼ�����b
		//xֵ�ϴ��Node���ȼ��ͣ�xС��Node���ڶ�ǰ��
		return a.triggerTime > b.triggerTime;
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
	friend class CEProcess;
public:
	static void initialize();
	static void runProcessQueue();
	static void buildGraph();
	static void rebuildGraph();

	//�������ȼ�����
	static void buildTriggerTimePriorityQueue();
private:

	//currently it is only for CQProcess.
	static priority_queue<Process_TriggerTime*, vector<Process_TriggerTime*> > cq_pq;

	static priority_queue<Process_TriggerTime*, vector<Process_TriggerTime*> > cep_pq;
};


