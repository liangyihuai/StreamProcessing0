#include "stdafx.h"

#include "RTreeCQIndex.h"
#include "ProcessRegisterForCQIndex.h"

RTreeCQIndex::RTreeCQIndex(int dimension, string eventType) {
	this->dimension = dimension;
	this->eventType = eventType;

	initialize();
}

void RTreeCQIndex::initialize() {
	Tools::PropertySet* ps = GetDefaults();
	Tools::Variant var;

	var.m_varType = Tools::VT_ULONG;
	var.m_val.ulVal = RT_RTree;
	ps->setProperty("IndexType", var);

	var.m_varType = Tools::VT_ULONG;
	var.m_val.ullVal = RT_Memory;
	ps->setProperty("IndexStorageType", var);

	var.m_varType = Tools::VT_ULONG;
	var.m_val.ulVal = dimension;
	ps->setProperty("Dimension", var);

	if (dimension <= 0)
		throw "dimension <= 0";

	Index * idx = new Index(*ps);
	delete ps;

	if (!idx->index().isIndexValid())
		throw "Failed to create valid index";
	else
		cout << "created index" << endl;

	this->idx = idx;
}

void RTreeCQIndex::buildIndex(Condition* condition) {
	
}

list<Process*> RTreeCQIndex::filter(EventPtr e) {
	Point* point = transformEventToPoint(e);

	ObjVisitor* visitor = new ObjVisitor;
	IShape* r = point;
	idx->index().intersectsWithQuery(*r, *visitor);

	int64_t nResultCount = visitor->GetResultCount();
	vector<IData*>& results = visitor->GetResults();

	vector<int64_t> *resultForId = new vector<int64_t>();
	for (int64_t i = 0; i < nResultCount; i++) {
		resultForId->push_back(results[i]->getIdentifier());
	}
	delete visitor;

	return ProcessRegisterForCQIndex::getProcess(*resultForId);
}


void RTreeCQIndex::addRegion(SpatialIndex::Point low, SpatialIndex::Point high, int64_t id) {
	uint8_t * pData = 0;
	uint32_t nDataLength = 0;

	SpatialIndex::IShape* shape = new SpatialIndex::Region(low, high);

	idx->index().insertData(nDataLength, pData, *shape, id);

	cout << "Rectangle " << id << " inserted into index." << endl;
	delete shape;
}

vector<IData*>* RTreeCQIndex::getIntersectedRegion(Point * p) {
	ObjVisitor* visitor = new ObjVisitor;

	IShape* r = p;

	idx->index().intersectsWithQuery(*r, *visitor);

	int64_t nResultCount;
	nResultCount = visitor->GetResultCount();

	vector<IData*>& results = visitor->GetResults();
	vector<IData*> * resultsCopy = new vector<IData*>();

	for (int64_t i = 0; i < nResultCount; i++) {
		resultsCopy->push_back(dynamic_cast<IData*>(results[i]->clone()));
	}

	delete visitor;
	cout << "found " << nResultCount << " results. " << endl;

	return resultsCopy;
}


