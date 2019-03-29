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
维护一个输入队列不为空的cp队列，循环消费cp中输入队列中的数据，直到cp队列为空。
1. 在输入队列不为空的时候，将相应的队列加入cp队列中.
2. 不断从cp队列头部弹出一个cp，消费cp的输入队列timeSlice个数据或者队列为空。如果消费了timeSlice个数据之后，该队列不为空，
就将其添加到cp队列的尾部。如果该cp有多个输入队列，只要有一个队列为空，就不将该cp加入cp队列中。
*/
class ExecuteScheduler {
public:
	static void initialize();
	static void runProcessQueue();
	
public:
	static void buildGraph();
};
