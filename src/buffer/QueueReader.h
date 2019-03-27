#pragma once

#include "Queue.h"
#include "QueueWriter.h"

class QueueReader : public Queue {
private:
	//the stream that this reader reads.
	string streamName;

	/// System-wide unique id
	//unsigned int id;

	/// shared writer queue from which we read dequeues
	QueueWriter *writer;

	/// The Id by which we identify ourselves to the writer
	unsigned int readerId;
public:
	QueueReader();
	~QueueReader();

	//------------------------------------------------------------
	// Initialization routines
	//------------------------------------------------------------
	void setWriter(QueueWriter *writer);
	void setStreamName(string stream);
	string getStreamName();

	//------------------------------------------------------------
	// Inherited from Queue
	//------------------------------------------------------------
	bool enqueue(EventPtr e); // not implemented
	EventPtr dequeue();
	EventPtr peek() const;
	bool isFull() const;
	bool isEmpty() const;
};
