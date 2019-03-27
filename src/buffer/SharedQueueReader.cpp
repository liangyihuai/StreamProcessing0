//
// Created by USER on 12/5/2018.
//
#include "../stdafx.h"
//#include "SharedQueueReader.h"
//
//
//SharedQueueReader::SharedQueueReader(){
//    // this->id = id;
//    this->writer = 0;
//}
//
//SharedQueueReader::~SharedQueueReader() {}
//
//int SharedQueueReader::setWriter(SharedQueueWriter *writer)
//{
//    assert(writer);
//
//    this->writer = writer;
//    return 1;
//}
//
//int SharedQueueReader::setReaderId(unsigned int readerId)
//{
//    this->readerId = readerId;
//    return 1;
//}
//
//bool SharedQueueReader::enqueue(EventPtr e)
//{
//    // should never be called
//    assert(0);
//
//    return 0;
//}
//
//EventPtr SharedQueueReader::dequeue()
//{
//    return writer->dequeue(readerId);
//}
//
//EventPtr SharedQueueReader::peek() const{
//	return writer->peek(readerId);
//}
//
//bool SharedQueueReader::isFull() const
//{
//    return writer->isFull(readerId);
//}
//
//bool SharedQueueReader::isEmpty() const
//{
//    return writer->isEmpty(readerId);
//}
//
//void SharedQueueReader::setStreamName(string stream){
//    this->streamName = stream;
//}
//
//string SharedQueueReader::getStreamName(){
//    return this->streamName;
//}