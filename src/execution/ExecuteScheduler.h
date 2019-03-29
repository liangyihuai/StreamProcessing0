#pragma once

#include <unordered_map>
#include "EventProcess.h"
#include "EventCapture.h"
#include "CQProcess.h"
#include "CEPProcess.h"
#include "Process.h"
#include "TopoGraph.h"
#include "ProcessRegister.h"

/*
ά��һ��������в�Ϊ�յ�cp���У�ѭ������cp����������е����ݣ�ֱ��cp����Ϊ�ա�
1. ��������в�Ϊ�յ�ʱ�򣬽���Ӧ�Ķ��м���cp������.
2. ���ϴ�cp����ͷ������һ��cp������cp���������timeSlice�����ݻ��߶���Ϊ�ա����������timeSlice������֮�󣬸ö��в�Ϊ�գ�
�ͽ�����ӵ�cp���е�β���������cp�ж��������У�ֻҪ��һ������Ϊ�գ��Ͳ�����cp����cp�����С�
*/
class ExecuteScheduler {
public:
	static void initialize();
	static void runProcessQueue();
	
public:
	static void buildGraph();
};
