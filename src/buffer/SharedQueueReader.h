////
//// Created by USER on 12/4/2018.
////
//
//#ifndef CONTINUOUSPROCESSING_SHAREDQUEUEREADER_H
//#define CONTINUOUSPROCESSING_SHAREDQUEUEREADER_H
//#include "Queue.h"
//#include "SharedQueueWriter.h"
//
///*
// *  *      setup
// *1. for reader, set reader Id from 0.
// *2. for reader, set writer for each reader
// *3. for writer, set reader num for writer
// */
//class SharedQueueReader : public Queue {
//private:
//    //the stream that this reader reads.
//    string streamName;
//
//    /// System-wide unique id
//    //unsigned int id;
//
//    /// shared writer queue from which we read dequeues
//    SharedQueueWriter *writer;
//
//    /// The Id by which we identify ourselves to the writer
//    unsigned int readerId;
//public:
//    SharedQueueReader();
//    ~SharedQueueReader();
//
//    //------------------------------------------------------------
//    // Initialization routines
//    //------------------------------------------------------------
//    int setWriter(SharedQueueWriter *writer);
//    int setReaderId(unsigned int readerId);
//    void setStreamName(string stream);
//    string getStreamName();
//
//    //------------------------------------------------------------
//    // Inherited from Queue
//    //------------------------------------------------------------
//    bool enqueue(EventPtr e); // not implemented
//    EventPtr dequeue();
//    EventPtr peek() const;
//    bool isFull() const;
//    bool isEmpty() const;
//};
//
//
//#endif //CONTINUOUSPROCESSING_SHAREDQUEUEREADER_H
