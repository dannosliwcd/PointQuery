#include "KDTreePointFinder.h"
#include "CountyRecord.h"
#include "MaxHeap.h"
#include <memory>
#include <tuple>
#include <cmath>
#include <utility>

// Availability of M_PI is unpredictiable. Just define pi here.
#define KD_PI 3.14159265358979323846

#include <iostream>

struct KDNode final
{
	std::unique_ptr<KDNode> m_left;
	std::unique_ptr<KDNode> m_right;
	bool m_isLongitude; // For more than 2 dimensions, make this an int and run levels modulo to this
	CountyRecord m_record;
};

template<typename Comparison>
static size_t Partition(std::vector<CountyRecord>& records, size_t left, size_t right, size_t pivot, Comparison compare)
{
	auto pivotRecord = records[pivot];
	std::swap(records[pivot], records[right]);
	auto partitionIndex = left;
	for (auto i = left; i < right; ++i)
	{
		if (compare(records[i], pivotRecord))
		{
			std::swap(records[partitionIndex], records[i]);
			++partitionIndex;
		}
	}

	std::swap(records[right], records[partitionIndex]);
	return partitionIndex;
}

// Get the kth record, partially sorting the collection of records as we go.
template<typename Comparison>
static void QuickSelect(std::vector<CountyRecord>& records, size_t left, size_t right, size_t k, Comparison compare)
{
	while(true)
	{
		if (left == right)
		{
			return;
		}
		auto pivot = left + (rand() % (right - left + 1));
		pivot = Partition(records, left, right, pivot, compare);
		if (k == pivot)
		{
			return;
		}
		else if (k < pivot)
		{
			right = pivot - 1;
		}
		else
		{
			left = pivot + 1;
		}
	}
}

template<typename Comparison>
static void sortToMedian(std::vector<CountyRecord>& records, Comparison compare)
{
	//std::sort(records.begin(), records.end(), compare);
	QuickSelect(records, 0, records.size() - 1, records.size() / 2, compare);
}

// Insert the records to the KD tree in a manner that should lead to a
// more balanced tree.
// TODO: Consider applying the projection at this step. Center the projection around the center of our records.
std::unique_ptr<KDNode> KDTreePointFinder::BuildTree(
		std::vector<CountyRecord> records,
		bool useLongitude)
{
	if (records.empty())
	{
		return nullptr;
	}

	sortToMedian(records, [useLongitude](const CountyRecord& lhs, const CountyRecord& rhs)
			{
				return useLongitude
					? lhs.m_longitude < rhs.m_longitude
					: lhs.m_latitude < rhs.m_latitude;
			});
	auto midpoint = records.size() / 2; 
	auto medianRecord = records[midpoint];

	// Split into (left, <remove the split point>, right)
	auto left = BuildTree(std::vector<CountyRecord>(records.begin(), records.begin() + midpoint), !useLongitude);
	auto right = BuildTree(std::vector<CountyRecord>(records.begin() + midpoint + 1, records.end()), !useLongitude);
	std::vector<CountyRecord>().swap(records);
	
	// Keep data points in all nodes
	return std::unique_ptr<KDNode>(new KDNode{
			std::move(left),
			std::move(right),
			useLongitude, // TODO: remove this, base on level?
			medianRecord});
}

KDTreePointFinder::KDTreePointFinder(
		const std::vector<CountyRecord>& countyRecords)
	: m_root(BuildTree(countyRecords, true))
{
}

KDTreePointFinder::~KDTreePointFinder()
{
}

// Calculate the distance between two points, using an equirectangular approximation
// http://www.movable-type.co.uk/scripts/latlong.html
static float Distance(float latitude1, float longitude1, float latitude2, float longitude2)
{
	// TODO: Can store lambda and phi instead of lat and long
	auto lambda1 = longitude1 * KD_PI / 180;
	auto lambda2 = longitude2 * KD_PI / 180;
	auto phi1 = latitude1 * KD_PI / 180;
	auto phi2 = latitude2 * KD_PI / 180;
	static const auto EARTH_RADIUS_METERS = 6371e3;
	
	auto x = (lambda2 - lambda1) * std::cos((phi1 + phi2) / 2);
	auto y = phi2 - phi1;
	// TODO: Can remove the radius and sqrt since this is only for relative comparisons.
	return std::sqrt(x * x + y * y) * EARTH_RADIUS_METERS;
}

// Find k nearest neighbors
// Nice visual guide at:
// https://gopalcdas.com/2017/05/24/construction-of-k-d-tree-and-using-it-for-nearest-neighbour-search/
std::vector<CountyRecord> KDTreePointFinder::FindNearest(
		decltype(CountyRecord::m_latitude) latitude,
		decltype(CountyRecord::m_latitude) longitude,
		unsigned int nearestCount)
{
	// Keep the best distances in a max heap. The worst of the best are the
	// first to remove, so we will eventually have it full with only the best.
	MaxHeap<float, CountyRecord*> nearestCounties(nearestCount);

	// tuple<do_left_prune_check, parent_axis_split, current_node>
	std::vector<std::tuple<bool, float, KDNode*> > nextNodeStack {
		std::make_tuple(true, 1e3, m_root.get())
	}; // TODO: verify: max stack height is lg(n)?
	
	while (!nextNodeStack.empty())
	{
		KDNode* node;
		float parentSplit;
		bool doLeftCheck;
		std::tie(doLeftCheck, parentSplit, node) = nextNodeStack.back();
		nextNodeStack.pop_back();

		if (!node)
		{
			continue;
		}


		// Skip this node and children if the node parent's split is so far from
		// the query that the node cannot possibly contain a better point.
		//
		// Note that we only want to prune once the knn heap is full. Any point is
		// a candidate if it can be added to the heap.
		//
		// TODO: Right now this necessarily performs a distance calculation. The
		// prune can still help because children of this node will not be calculated,
		// but see if there's a way to do any precalculation that can make this a
		// simple subtraction instead.
		//
		// Live distance calculation is needed because we are working
		// with an equirectangular projection. Distance measurements
		// are impacted by your choice of central point for the
		// projection.
		if (!nearestCounties.IsEmpty() && nearestCounties.IsFull())
		{
			if (doLeftCheck)
			{
				if (node->m_isLongitude)
				{
					auto distance = Distance(latitude, parentSplit, longitude, longitude);
					if (distance > nearestCounties.GetMax().p && latitude < parentSplit)
					{
						continue;
					}
				}
				else
				{
					auto distance = Distance(latitude, latitude, longitude, parentSplit);
					if (distance > nearestCounties.GetMax().p && longitude < parentSplit)
					{
						continue;
					}
				}
			}
			else
			{
				if (node->m_isLongitude)
				{
					auto distance = Distance(latitude, parentSplit, longitude, longitude);
					if (distance > nearestCounties.GetMax().p && latitude > parentSplit)
					{
						continue;
					}
				}
				else
				{
					auto distance = Distance(latitude, latitude, longitude, parentSplit);
					if (distance > nearestCounties.GetMax().p && longitude > parentSplit)
					{
						continue;
					}
				}
			}
		}

		auto distance = Distance(latitude, longitude, node->m_record.m_latitude, node->m_record.m_longitude);
		if (nearestCounties.IsEmpty() || distance < nearestCounties.GetMax().p)
		{
			if (nearestCounties.IsFull())
		       	{
				nearestCounties.RemoveMax();
			}
			nearestCounties.Insert(distance, &node->m_record);
		}

		// Go first to branches we think are more likely to improve our
		// results. Early improvement may mean we can ignore the other
		// branch when we reach it.
		auto splitValue = node->m_isLongitude
		       	? node->m_record.m_longitude : node->m_record.m_latitude;
		auto queryAxisValue = node->m_isLongitude
			? longitude : latitude;
		if (queryAxisValue <= splitValue)
		{
			// Go left first
			nextNodeStack.emplace_back(true, splitValue, node->m_right.get());
			nextNodeStack.emplace_back(false, splitValue, node->m_left.get());
		}
		else
		{
			// Go right first
			nextNodeStack.emplace_back(false, splitValue, node->m_left.get());
			nextNodeStack.emplace_back(true, splitValue, node->m_right.get());
		}
	}

	std::vector<CountyRecord> records;
	records.reserve(nearestCounties.GetSize());
	while (!nearestCounties.IsEmpty())
	{
		records.emplace_back(*nearestCounties.GetMax().e);
		nearestCounties.RemoveMax();
	}
	return records;
}
