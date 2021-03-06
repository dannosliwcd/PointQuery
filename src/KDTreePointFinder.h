#ifndef KDTREEPOINTFINDER_H
#define KDTREEPOINTFINDER_H
#include "CountyRecord.h"
#include "PointFinder.h"
#include "MaxHeap.h"
#include <memory>
#include <vector>
#include <type_traits>

struct KDNode;

// KD Tree implementation hard-coded to work with 2-dimensional CountyRecord entries.
class KDTreePointFinder final : public PointFinder
{
public:
	KDTreePointFinder(const std::vector<CountyRecord>& countyRecords);
	virtual ~KDTreePointFinder();
	virtual std::vector<std::pair<float, CountyRecord> > FindNearest(
			decltype(CountyRecord::m_latitude) latitude,
			decltype(CountyRecord::m_latitude) longitude,
			unsigned int nearestCount) override;

private:
	// To remove this assertion, we would need to be smarter with m_split
	static_assert(std::is_same<decltype(CountyRecord::m_latitude), decltype(CountyRecord::m_longitude)>::value,
			"KDTreePointFinder dimensions must be of the same type");

	static std::unique_ptr<KDNode> BuildTree(std::vector<CountyRecord> records, bool useLongitude);

	std::unique_ptr<KDNode> m_root;
};

#endif //KDTREEPOINTFINDER_H
