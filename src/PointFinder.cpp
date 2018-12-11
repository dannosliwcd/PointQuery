#include "PointFinder.h"
#include "QuadTreePointFinder.h"
#include "KDTreePointFinder.h"
#include "HeapPointFinder.h"
#include <stdexcept>

PointFinder::PointFinder()
{
}

PointFinder::~PointFinder()
{
}

std::unique_ptr<PointFinder>
PointFinder::Make(Method method, const std::vector<CountyRecord>& countyRecords)
{
	switch (method)
	{
		case Method::KDTree:
			return std::unique_ptr<PointFinder>(new KDTreePointFinder(countyRecords));
		case Method::QuadTree:
			return std::unique_ptr<PointFinder>(new QuadTreePointFinder(countyRecords));
		case Method::Heap:
			return std::unique_ptr<PointFinder>(new HeapPointFinder(countyRecords));
	}
	throw std::runtime_error("Unknown search method specified");
}
