#include <PointFinder.h>
#include <CountyRecord.h>
#include <catch.hpp>
#include <string>

TEST_CASE("search in empty finder")
{
	std::vector<CountyRecord> records;
	auto finder = PointFinder::Make(PointFinder::Method::KDTree, records);
	REQUIRE_THROWS(finder->FindNearest(0, 0, 1));
	finder = PointFinder::Make(PointFinder::Method::QuadTree, records);
	REQUIRE_THROWS(finder->FindNearest(0, 0, 1));
}
