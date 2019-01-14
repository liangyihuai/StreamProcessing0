//
// Created by USER on 12/4/2018.
//
#include "stdafx.h"
#include "DerivedEventStore.h"
#include "QueueWriter.h"

//stream name -> shared queue writer
std::unordered_map<std::string, QueueWriter*> DerivedEventStore::queueWriterMap;

//unsigned int DerivedEventStore::sharedQueueID = 0;

//store stream name that is not empty
std::set<std::string> DerivedEventStore::unemptyStreams;

//stream name -> share queue reader
std::unordered_map<std::string, std::list<QueueReader*>*> DerivedEventStore::queueReaderMap;

void DerivedEventStore::addEvent(std::string stream, EventPtr e){
    if(queueWriterMap.find(stream) == queueWriterMap.end()){
        queueWriterMap[stream] = new QueueWriter();
    }
    queueWriterMap[stream]->enqueue(e);
    unemptyStreams.insert(stream);
}

void DerivedEventStore::registerReader(string stream, QueueReader* reader){
	if (!reader) {
		LOG(ERROR) << "reader is null";
		throw runtime_error("");
	}

	reader->setStreamName(stream);

    if(queueReaderMap.find(stream) == queueReaderMap.end()){
        queueReaderMap[stream] = new list<QueueReader*>();
    }
    list<QueueReader*>* li = queueReaderMap[stream];
    li->push_back(reader);

    if(queueWriterMap.find(stream) == queueWriterMap.end()){
        queueWriterMap[stream] = new QueueWriter();
    }
    QueueWriter * writer = queueWriterMap[stream];
    reader->setWriter(writer);
}


DerivedEventStore::~DerivedEventStore(){
    for(auto iter = queueReaderMap.begin(); iter != queueReaderMap.end(); iter++){
        list<QueueReader*>* li = iter->second;
        //delete reader in CPProcess or CEPProcess
//        for(QueueReader* r: *li){
//            delete r;
//            r = nullptr;
//        }
        li->clear();
        delete iter->second;
        iter->second = nullptr;
    }

    for(auto iter = queueWriterMap.begin(); iter != queueWriterMap.end(); iter++){
        delete iter->second;
        iter->second = nullptr;
    }
}