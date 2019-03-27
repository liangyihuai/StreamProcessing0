//
// Created by USER on 12/4/2018.
//

#ifndef CONTINUOUSPROCESSING_QUEUE_H
#define CONTINUOUSPROCESSING_QUEUE_H


#include "../common/Event.h"

/**
* Queues are entities that connect different operators and define the
* paths through which tuples flow in the system.
*
* Conceptualy, each queue has one operator inserting elements into the
* queue, and one operator reading off elements from the queue.
*/
class Queue {
public:
    virtual ~Queue() {}

    /**
     * Enqueue a new element into the queue.
     *
     * @param  element     The element to be enqueued
     * @return             True if enqueue succeeded, false otherwise
     */
    virtual bool enqueue(EventPtr e) = 0;

    /**
     * Dequeue the oldest element from the queue.
     *
     * @param  element     (output) The dequeued element.
     * @return             True if an element was dequeued, false
     *                     otherwise
     */
    virtual EventPtr dequeue() = 0;

    /**
     * Peek @ the oldest element without dequeueing.
     *
     * @param element     (output) the oldest element
     * @return            True if queue is nonempty, false otherwise
     */
    virtual EventPtr peek() const = 0;

    /**
     * @return true if the queue is full, false otherwise.
     */
    virtual bool isFull() const = 0;

    /**
     * @return true if the queue is empty, false otherwise.
     */
    virtual bool isEmpty() const = 0;

	/**
	* only implemented by queue writer
	*/
	virtual int size() const { 
		std::cout << "function size is not implemented";
		throw runtime_error("");
	}
};
#endif //CONTINUOUSPROCESSING_QUEUE_H
