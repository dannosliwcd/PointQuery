#include <PointFinder.h>
#include <QuadTreePointFinder.h>
#include <KDTreePointFinder.h>

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
		case Method::Linear:
			throw std::runtime_error("Linear search method not yet implemented");
	}
	throw std::runtime_error("Unknown search method specified");
}
