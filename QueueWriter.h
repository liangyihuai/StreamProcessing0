#pragma once
#include "Queue.h"

class QueueWriter :public Queue{
private:
	/// System-wide unique id
	//unsigned int id;

	/// Maximum number of elements I can hold
	static const unsigned int MAX_ELEMENTS = 100;

	/// Maximum number of readers we allow
	static const unsigned int MAX_READERS = 10;

	/// The next dequeue element for each reader
	int nextDequeue[MAX_READERS];

	int numReader = 0;

	/// the head of the queue, always an empty element
	int head = -1;

	/// the oldest element in the queue, if head == tail, the queue is empty
	int tail = -1;

	/// Total number of dequeues by a reader
	unsigned int totalDequeued[MAX_READERS];

	/// Total number of enqueues
	unsigned int totalEnqueued = 0;

	/// The reader who lags behind the most
	unsigned int slowestReader = 0;

	EventPtr queue[MAX_ELEMENTS];
public:
	//readerNum plus one
	void increaseReaderNum();

	int getReaderNum();

	//------------------------------------------------------------
	// Inherited from Queue
	//------------------------------------------------------------
	int size() const;
	bool enqueue(EventPtr e);
	EventPtr dequeue(); // not implemented
	EventPtr peek() const; // not implemented
	bool isFull() const;
	bool isEmpty() const; // not implemented

	//------------------------------------------------------------
	// Called by the reader
	//------------------------------------------------------------
	EventPtr dequeue(unsigned int readerId);
	EventPtr peek(unsigned int readerId)const;
	bool isFull(unsigned int readerId) const;
	bool isEmpty(unsigned int readerId) const;

	QueueWriter();
	~QueueWriter();
};

