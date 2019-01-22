#pragma once
//the interface of process, including event filter, event capture, cq, cep

class Process {
public:
	/*insert event to the window of operator from input queues.
	this function is called by a time scheduler. 
	Return false, the process needs to push back to the CP queue.
	*/
	virtual bool process(int timeSlice) = 0;

	void setId(int _id) { id = _id; };
	int getId() { return id; }
private:
	int id;
};