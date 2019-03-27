#include "../stdafx.h"
#include "QueueWriter.h"

void QueueWriter::increaseReaderNum() {
	numReader++;
}

int QueueWriter::getReaderNum() {
	return numReader;
}

int QueueWriter::size() const {
	return totalEnqueued - totalDequeued[slowestReader];
}

bool QueueWriter::enqueue(EventPtr e) {
	if (isFull()) return false;
	if (head == -1) {
		queue[0] = e;
		tail = 0;
		head = 1;
	}
	else {
		queue[head++ % MAX_ELEMENTS] = e;
	}
	totalEnqueued++;
	return true;
}

EventPtr QueueWriter::dequeue() {
	std::cout << "function \"dequeue\" is not implemented";
	throw runtime_error("not implemented");
}

EventPtr QueueWriter::peek() const {
	std::cout << "function \"peek\" is not implemented";
	throw runtime_error("not implemented");
}

bool QueueWriter::isFull() const {
	return (head + 1) % MAX_ELEMENTS == tail;
}

EventPtr QueueWriter::dequeue(unsigned int readerId) {
	if (isEmpty(readerId)) {
		std::cout << "the queue is empty";
		throw runtime_error("");
	}

	if (nextDequeue[readerId] == -1) {
		nextDequeue[readerId] = tail;
	}
	int nextDequeueIndex = nextDequeue[readerId];

	EventPtr result = queue[nextDequeueIndex];
	nextDequeue[readerId] = (++nextDequeueIndex) % MAX_ELEMENTS;

	if (readerId == slowestReader) {
		unsigned int totalDequeuedR = totalDequeued[readerId];

		for (int i = 0; i < numReader; i++) {
			totalDequeued[i] -= totalDequeuedR;
			if ((totalDequeued[i] == 0) && (i != readerId)) {
				slowestReader = i;
			}
		}
		totalEnqueued -= totalDequeuedR;
		totalDequeued[readerId] = 1;
		if (readerId == slowestReader) {
			tail = (++tail) % MAX_ELEMENTS;
		}
	}
	else {
		totalDequeued[readerId]++;
	}

	return result;
}

EventPtr QueueWriter::peek(unsigned int readerId)const {
	if (isEmpty(readerId)) {
		std::cout << "the queue is empty";
		throw runtime_error("");
	}
	if (nextDequeue[readerId] == -1) {
		return queue[tail];
	}
	else {
		return queue[nextDequeue[readerId]];
	}
}

bool QueueWriter::isFull(unsigned int readerId) const {
	std::cout << "not implemented";
	throw runtime_error("");
}

bool QueueWriter::isEmpty(unsigned int readerId) const {
	if(isEmpty()) return true;//check the writer queue
	
	return totalEnqueued - totalDequeued[readerId] == 0;
}


bool QueueWriter::isEmpty() const {
	return tail == head;
}

QueueWriter::QueueWriter(){
	for (int i = 0; i < MAX_READERS; i++) {
		totalDequeued[i] = 0;
		nextDequeue[i] = -1;
	}
}

QueueWriter::~QueueWriter(){

}
