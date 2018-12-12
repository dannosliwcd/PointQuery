#ifndef HEAPPOINTFINDER_H
#define HEAPPOINTFINDER_H
#include <CountyRecord.h>
#include <PointFinder.h>
#include <vector>
#include <utility>

// This implementation linearly searches all points and adds them to a haxheap to find the K nearest points.
class HeapPointFinder final : public PointFinder
{
public:
	HeapPointFinder(const std::vector<CountyRecord>& countyRecords);
	virtual ~HeapPointFinder();
	virtual std::vector<std::pair<float, CountyRecord> > FindNearest(
			decltype(CountyRecord::m_latitude) latitude,
			decltype(CountyRecord::m_latitude) longitude,
			unsigned int nearestCount) override;

private:
	std::vector<CountyRecord> m_records;
};

#endif //HEAPPOINTFINDER_H
