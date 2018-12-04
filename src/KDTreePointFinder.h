#ifndef KDTREEPOINTFINDER_H
#define KDTREEPOINTFINDER_H
#include <CountyRecord.h>
#include <PointFinder.h>
#include <memory>
#include <vector>

class KDTreePointFinder final : public PointFinder
{
public:
	KDTreePointFinder(const std::vector<CountyRecord>& countyRecords);
	virtual ~KDTreePointFinder();
	virtual std::vector<CountyRecord> FindNearest(
			decltype(CountyRecord::m_latitude) lat,
			decltype(CountyRecord::m_latitude) longitude,
			unsigned int nearestCount) override;
};

#endif //KDTREEPOINTFINDER_H
