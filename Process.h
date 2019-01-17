#pragma once
//the interface of process, including event filter, event capture, cq, cep

class Process {
public:
	virtual void process(int timeSlice) = 0;
};