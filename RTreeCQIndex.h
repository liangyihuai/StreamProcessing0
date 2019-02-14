#pragma once

#include "CQIndex.h"
#include <spatialindex/capi/sidx_api.h>
#include <spatialindex/capi/sidx_impl.h>
#include <spatialindex/capi/sidx_config.h>

using namespace SpatialIndex;

class RTreeCQIndex: public CQIndex{
public:
	RTreeCQIndex(int dimension, string eventType);

	~RTreeCQIndex();


	//--------------------------
	//interface CQIndex
	//--------------------------
	void buildIndex(Condition*) override;

	list<Process*> filter(EventPtr) override;


	//---------------------------
	//others
	//---------------------------
	void initialize();

	Point* transformEventToPoint(EventPtr);

private:
	void RTreeCQIndex::addRegion(SpatialIndex::Point low, SpatialIndex::Point high, int64_t id);
	vector<IData*>* getIntersectedRegion(Point * p);
private:
	Index * idx;

	int dimension;

	string eventType;
};


