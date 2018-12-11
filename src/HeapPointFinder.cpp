#include "HeapPointFinder.h"
#include "CountyRecord.h"
#include "MaxHeap.h"
#include <cmath>

// Availability of M_PI is unpredictiable. Just define pi here.
#define KD_PI 3.14159265358979323846

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

HeapPointFinder::HeapPointFinder(
		const std::vector<CountyRecord>& countyRecords)
	: m_records(countyRecords)
{
}

HeapPointFinder::~HeapPointFinder()
{
}

std::vector<CountyRecord> HeapPointFinder::FindNearest(
		decltype(CountyRecord::m_latitude) latitude,
		decltype(CountyRecord::m_latitude) longitude,
		unsigned int nearestCount)
{
	MaxHeap<float, const CountyRecord*> nearestCounties(nearestCount);
	for (const auto& record : m_records)
	{
		auto distance = Distance(latitude, longitude, record.m_latitude, record.m_longitude);
		if (nearestCounties.IsFull())
		{
			if (distance < nearestCounties.GetMax().p)
			{
				nearestCounties.RemoveMax();
				nearestCounties.Insert(distance, &record);
			}
		}
		else
		{
			nearestCounties.Insert(distance, &record);
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
