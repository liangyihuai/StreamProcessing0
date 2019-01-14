#include "stdafx.h"
#include "QueueReader.h"

QueueReader::QueueReader() {
	readerId = 0;
}

QueueReader::~QueueReader() {
}

//------------------------------------------------------------
// Initialization routines
//------------------------------------------------------------
void QueueReader::setWriter(QueueWriter *writer) {
	this->writer = writer;
	this->readerId = writer->getReaderNum();
	writer->increaseReaderNum();
}

void QueueReader::setStreamName(string stream) {
	this->streamName = stream;
}

string QueueReader::getStreamName() {
	return streamName;
}

//------------------------------------------------------------
// Inherited from Queue
//------------------------------------------------------------

bool QueueReader::enqueue(EventPtr e) { // not implemented
	LOG(ERROR) << "function \"enqueue\" is not implemented";
	throw runtime_error("");
}

EventPtr QueueReader::dequeue() {
	return writer->dequeue(readerId);
}

EventPtr QueueReader::peek() const {
	return writer->peek(readerId);
}

bool QueueReader::isFull() const {
	LOG(ERROR) << "function \"isFull\" is not implemented";
	throw runtime_error("not implemented");
}

bool QueueReader::isEmpty() const {
	return writer->isEmpty(readerId);
}