//
// Created by USER on 12/5/2018.
//

#include "stdafx.h"
//#include "SharedQueueWriter.h"
//
//
//SharedQueueWriter::SharedQueueWriter (){
//    // this -> id = id;
//    this->queueSize = 0;
//    queueHead = new Element();
//    queueTail = queueHead;
//
//    this->slowestReader = 0;
//    for(int i = 0; i < MAX_READERS; i++){
//        this->nextDequeue[i] = nullptr;
//        this->totalDequeued[i] = 0;
//    }
//}
//
//int SharedQueueWriter::size(){
//    return  this->queueSize;
//}
//
//void SharedQueueWriter::setMaxElements(unsigned int me){
//    this->maxElements = me;
//}
//
//
//bool SharedQueueWriter::enqueue(EventPtr e) {
//    unsigned int numActiveElements = 0;
//
//    numActiveElements = totalEnqueued - totalDequeued[slowestReader];
//
//    assert(numActiveElements <= maxElements);
//
//    // no space
//    if (numActiveElements > maxElements) return false;
//    // enqueue
//    Element *ele = new Element(e);
//
//    if(queueHead == queueTail) {
//        queueHead->next = ele;
//        ele->prev = queueHead;
//        queueTail = ele;
//    }else{
//        Element *firstEle = queueHead->next;
//        ele->next = firstEle;
//        firstEle->prev = ele;
//
//        queueHead->next = ele;
//        ele->prev = queueHead;
//    }
//    //let the empty reader point to the first element
//    for(int i = 0; i < numReaders; i++) {
//        if(!nextDequeue[i] || nextDequeue[i] == queueHead)
//            nextDequeue[i] = queueHead->next;
//    }
//
//    totalEnqueued++;
//
//    queueSize++;
//    return true;
//}
//
//EventPtr SharedQueueWriter::dequeue() {
//    throw "never used";
//}
//
//EventPtr SharedQueueWriter::peek() const {
//    throw "never used";
//}
//
//bool SharedQueueWriter::isFull() const {
//    assert(totalEnqueued - totalDequeued[slowestReader] <= maxElements);
//    return (totalEnqueued - totalDequeued[slowestReader] == maxElements);
//}
//
//bool SharedQueueWriter::isEmpty() const{
//    throw "never used";
//}
//
//EventPtr SharedQueueWriter::dequeue(unsigned int reader) {
//    unsigned int totalDequeued_r = 0;
//    EventPtr result = nullptr;
//
//    assert(reader < numReaders);
//    assert(totalEnqueued >= totalDequeued[reader]);
//
//    if (totalEnqueued == totalDequeued[reader])
//        throw runtime_error("empty");
//    if(queueHead == queueTail)
//        throw runtime_error("queueHead == queueTail, queue is empty");
//
//	if (!nextDequeue[reader]) {
//		nextDequeue[reader] = queueTail;
//	}
//
//    Element * ele = nextDequeue[reader];
//    result = ele->event; //save the value of current element
//	if (result == nullptr) {
//		cout << "null";
//	}
//    nextDequeue[reader] = ele->prev; //move the pointer for this reader to previous element
//
//    if (reader == slowestReader) {
//        totalDequeued_r = totalDequeued[reader];
//
//        for (unsigned int r = 0; r < numReaders; r++) {
//            assert(totalDequeued_r <= totalDequeued[r]);
//
//            totalDequeued[r] -= totalDequeued_r;
//            if ((totalDequeued[r] == 0) && (r != reader)) {
//                slowestReader = r;
//            }
//        }
//        totalEnqueued -= totalDequeued_r;
//
//        totalDequeued[reader] = 1;
//        if (slowestReader == reader) {//release the memory
//
//            queueTail = ele->prev;
//
//            assert(queueSize > 0);
//            queueSize--;
//
//            ele->prev = nullptr;
//            ele->next = nullptr;
//            delete ele;
//            ele = nullptr;
//        }
//    }else {
//        totalDequeued[reader] ++;
//    }
//
//
//
//    return result;
//}
//
//EventPtr SharedQueueWriter::peek(unsigned int reader) const{
//    assert(reader < numReaders);
//    assert(totalEnqueued >= totalDequeued[reader]);
//
//    if (totalEnqueued == totalDequeued[reader])
//        return false;
//
//	return nextDequeue[reader]->event;
//}
//
//bool SharedQueueWriter::isFull(unsigned int reader) const{
//    assert(reader < numReaders);
//    assert(totalEnqueued >= totalDequeued[reader]);
//
//    return (totalEnqueued - totalDequeued[reader] == maxElements);
//}
//
//bool SharedQueueWriter::isEmpty(unsigned int reader) const{
//    assert(reader < numReaders);
//    assert(totalEnqueued >= totalDequeued[reader]);
//
//    //the writer queue is empty
//    if(queueSize == 0) return true;
//
//	if (nextDequeue[reader] == queueHead) return true;
//
//    //the reader queue is empty
//    return (totalEnqueued == totalDequeued[reader]);
//}
//
//int SharedQueueWriter::setNumReaders (unsigned int numReaders)
//{
//    if(numReaders > MAX_READERS) throw runtime_error("numReaders > MAX_READERS");
//    this -> numReaders = numReaders;
//    return 1;
//}