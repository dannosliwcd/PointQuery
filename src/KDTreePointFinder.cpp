#include <KDTreePointFinder.h>

KDTreePointFinder::KDTreePointFinder(
		const std::vector<CountyRecord>& countyRecords)
{
}

KDTreePointFinder::~KDTreePointFinder()
{
}

std::vector<CountyRecord> KDTreePointFinder::FindNearest(
		decltype(CountyRecord::m_latitude) lat,
		decltype(CountyRecord::m_latitude) longitude,
		unsigned int nearestCount)
{
	// TODO: Return the actual nearest points instead of an empty vector.
	return {};
}
