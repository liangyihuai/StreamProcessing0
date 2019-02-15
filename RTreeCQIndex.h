#pragma once

#include "CQIndex.h"
#include <spatialindex/capi/sidx_api.h>
#include <spatialindex/capi/sidx_impl.h>
#include <spatialindex/capi/sidx_config.h>

#include "CQIndexUtils.h"

using namespace SpatialIndex;

class RTreeCQIndex: public CQIndex{
public:
	RTreeCQIndex(int dimension, string eventType);

	~RTreeCQIndex();


	//--------------------------
	//interface CQIndex
	//--------------------------
	void buildIndex(Condition*, int64_t regionId) override;

	list<Process*> filter(EventPtr) override;


	//---------------------------
	//others
	//---------------------------
	void initialize();

private:
	void RTreeCQIndex::addRegion(SpatialIndex::Point low, SpatialIndex::Point high, int64_t id);

	const int MIN_BOUNDARY = -999999;
private:
	Index * idx;

	int dimension;

	string eventType;
};


