#ifndef POINTFINDER_H
#define POINTFINDER_H
#include <CountyRecord.h>
#include <memory>
#include <vector>

class PointFinder
{
public:
	enum class Method
	{
		Linear,
		QuadTree,
		KDTree
	};

	PointFinder();
	virtual ~PointFinder();
	virtual std::vector<CountyRecord> FindNearest(
			decltype(CountyRecord::m_latitude) lat,
			decltype(CountyRecord::m_latitude) longitude,
			unsigned int nearestCount) = 0;

	static std::unique_ptr<PointFinder> Make(
			Method method,
			const std::vector<CountyRecord>& countyRecords);
};

#endif //POINTFINDER_H
