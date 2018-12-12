#ifndef QUADTREEPOINTFINDER_H
#define QUADTREEPOINTFINDER_H
#include <CountyRecord.h>
#include <PointFinder.h>
#include <vector>

class QuadTreePointFinder final : public PointFinder
{
public:
	QuadTreePointFinder(const std::vector<CountyRecord>& countyRecords);
	virtual ~QuadTreePointFinder();
	virtual std::vector<std::pair<float, CountyRecord> > FindNearest(
			decltype(CountyRecord::m_latitude) lat,
			decltype(CountyRecord::m_latitude) longitude,
			unsigned int nearestCount) override;
	// TODO: add a member variable for your internal quadtree data structure
};

#endif //QUADTREEPOINTFINDER_H
