//
// Created by USER on 12/5/2018.
//

#ifndef CONTINUOUSPROCESSING_CQPROCESS_H
#define CONTINUOUSPROCESSING_CQPROCESS_H


#include "Event.h"
#include "Process.h"
#include <vector>
#include "QueueReader.h"
#include "Condition.h"
#include "Operator.h"
#include "ResultListener.h"
#include "Window.h"
#include "OperatorPredicate.h"
#include "EnhanceEventResult.h"
#include <unordered_map>

//the ResultListener return DerivedEventPtr.
class CQProcess: public Process{

private:

    // all stateless operatorPredicates and simple simple predicates share one queue reader.
	Predicate* predicate;
    QueueReader* reader = nullptr;

    //set up callback function to process the result of this query
    ResultListener* resultListener = nullptr;

    //sliding window, or tumble window or others
    Window * win;

    //the result name of stream after processing
    string outputStreamName;

public:
    //only class execution/ExecuteSchedule could access this method
    //before call it, the queue readers should be prepared.
    void process();

    void setPredicate(Predicate * pre);

    void setOutputStreamName(string stream);

    void setResultListener(ResultListener* listener);

    void setInputStream(string s);

    void setWindow(Window *w);

    QueueReader* getReader();

    ~CQProcess();

};
#endif //CONTINUOUSPROCESSING_CQPROCESS_H
