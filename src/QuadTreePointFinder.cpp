#include "CountyRecord.h"
#include <QuadTreePointFinder.h>

QuadTreePointFinder::QuadTreePointFinder(
		const std::vector<CountyRecord>& countyRecords)
{
	// TODO: countyRecords contains the raw list of county records.
	//       Insert those records into your internal data structure for
	//       the quad tree. You'll probably want to create a new member
	//       variable for QuadTreePointFinder in the header file and add
	//       the values there.
	//
	//       Don't worry about timing everything the CLI can handle that.
	//       We can write the timer code once in the CLI and it will be applied
	//       to all algorithms we use, instead of rewriting it for each algorithm.
}

QuadTreePointFinder::~QuadTreePointFinder()
{
}

std::vector<CountyRecord> QuadTreePointFinder::FindNearest(
		decltype(CountyRecord::m_latitude) lat,
		decltype(CountyRecord::m_latitude) longitude,
		unsigned int nearestCount)
{
	// TODO: Return the actual nearest points instead of an empty vector.
	//       Base your search on the member variable you created for the other TODO
	return {};
}
