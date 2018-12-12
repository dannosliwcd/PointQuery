#ifndef POINTFINDER_H
#define POINTFINDER_H
#include "CountyRecord.h"
#include <utility>
#include <memory>
#include <vector>

class PointFinder
{
public:
	enum class Method
	{
		Heap,
		QuadTree,
		KDTree
	};

	PointFinder();
	virtual ~PointFinder();
	virtual std::vector<std::pair<float, CountyRecord> > FindNearest(
			decltype(CountyRecord::m_latitude) lat,
			decltype(CountyRecord::m_latitude) longitude,
			unsigned int nearestCount) = 0;

	static std::unique_ptr<PointFinder> Make(
			Method method,
			const std::vector<CountyRecord>& countyRecords);
};

#endif //POINTFINDER_H
