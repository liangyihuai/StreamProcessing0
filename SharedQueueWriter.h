////
//// Created by USER on 12/4/2018.
////
//
//#ifndef CONTINUOUSPROCESSING_SHAREDQUEUEWRITER_H
//#define CONTINUOUSPROCESSING_SHAREDQUEUEWRITER_H
//
//
//#include "Queue.h"
//#include "Event.h"
//#include <cassert>
//#include <stdexcept>
//
//namespace queue {
//    class Element {
//    public:
//        EventPtr event;
//        Element * next = nullptr;
//        Element * prev = nullptr;
//
//        Element(){}
//        Element(EventPtr e):event(e) {}
//    };
//}
//
//using namespace queue;
//
///**
// * use link to implement a shared queue.
// *
// *      setup
// *1. for reader, set reader Id from 0.
// *2. for reader, set writer for each reader
// *3. for writer, set reader num for writer
// */
//class SharedQueueWriter : public Queue {
//private:
//    /// System-wide unique id
//    //unsigned int id;
//
//    /// Maximum number of elements I can hold
//    unsigned int maxElements = 20000;
//
//    /// Maximum number of readers we allow
//    static const unsigned int MAX_READERS = 10;
//
//    /// Number of readers
//    unsigned int numReaders = 0;
//
//    /// The next dequeue element for each reader
//    Element* nextDequeue[MAX_READERS];
//
//    /// the head of the queue, always an empty element
//    Element* queueHead = nullptr;
//
//    /// the oldest element in the queue, if head == tail, the queue is empty
//    Element* queueTail = nullptr;
//
//    /// Total number of dequeues by a reader
//    unsigned int totalDequeued[MAX_READERS];
//
//    /// Total number of enqueues
//    unsigned int totalEnqueued = 0;
//
//    /// The reader who lags behind the most
//    unsigned int slowestReader;
//
//    //the actual queue size.
//    unsigned int queueSize;
//
//public:
//    SharedQueueWriter ();
//
//    int setNumReaders (unsigned int numReaders);
//    void setMaxElements(unsigned int me);
//    int size();
//    //------------------------------------------------------------
//    // Inherited from Queue
//    //------------------------------------------------------------
//    bool enqueue(EventPtr e);
//    EventPtr dequeue(); // not implemented
//    EventPtr peek() const; // not implemented
//    bool isFull() const;
//    bool isEmpty() const; // not implemented
//
//    //------------------------------------------------------------
//    // Called by the reader
//    //------------------------------------------------------------
//    EventPtr dequeue(unsigned int readerId);
//    EventPtr peek(unsigned int readerId) const;
//    bool isFull(unsigned int readerId) const;
//    bool isEmpty(unsigned int readerId) const;
//
//};
//
//#endif //CONTINUOUSPROCESSING_SHAREDQUEUEWRITER_H
