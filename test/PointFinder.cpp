#include <PointFinder.h>
#include <CountyRecord.h>
#include <catch.hpp>
#include <string>

TEST_CASE("search in empty finder")
{
	std::vector<CountyRecord> records;
	auto finder = PointFinder::Make(PointFinder::Method::KDTree, records);
	REQUIRE(finder->FindNearest(0, 0, 1).empty());
	finder = PointFinder::Make(PointFinder::Method::QuadTree, records);
	REQUIRE(finder->FindNearest(0, 0, 1).empty());
}

TEST_CASE("search for exact points")
{
	auto test = [](PointFinder::Method method)
	{
		std::vector<CountyRecord> records {
			{"S1", "C1", 100, 200},
			{"S1", "C2", 100, 210},
			{"S1", "C3", 100, 220},
		};

		auto finder = PointFinder::Make(method, records);
		for (const auto& record : records)
		{
			auto nearest = finder->FindNearest(record.m_latitude, record.m_longitude, 1);
			REQUIRE(nearest.size() == 1);
			REQUIRE(record == nearest.front());
		}
	};

	SECTION("KD Tree")
	{
		test(PointFinder::Method::KDTree);
	}

	SECTION("QuadTree")
	{
		test(PointFinder::Method::QuadTree);
	}
}

TEST_CASE("Search for a trivially close point")
{
	auto test = [](PointFinder::Method method)
	{
		std::vector<CountyRecord> records {
			{"S1", "C1", 100, 200},
			{"S1", "C2", 100, 210},
			{"S1", "C3", 100, 220},
		};

		auto finder = PointFinder::Make(method, records);
		auto nearest = finder->FindNearest(101, 201, 1);
		REQUIRE(nearest.size() == 1);
		REQUIRE(records[0] == nearest.front());
	};

	SECTION("KD Tree")
	{
		test(PointFinder::Method::KDTree);
	}

	SECTION("QuadTree")
	{
		test(PointFinder::Method::QuadTree);
	}
}

TEST_CASE("bottom of valley")
{
	auto test = [](PointFinder::Method method)
	{
		std::vector<CountyRecord> records {
			{"S1", "C1", 4, 1},
			{"S1", "C2", 3, 1},
			{"S1", "C3", 2, -1},
			{"S1", "C4", 1, -1},
			{"S1", "C5", 0, 0},
			{"S1", "C6", 1, 1},
			{"S1", "C7", 2, 1},
			{"S1", "C8", 3, -1},
			{"S1", "C9", 4, -1},
		};

		// KD Tree should split in to left and right halves on the root
		auto finder = PointFinder::Make(method, records);
		auto nearest = finder->FindNearest(0, 0, 1);
		REQUIRE(nearest.size() == 1);
		REQUIRE(records[4] == nearest.front());
	};

	SECTION("KD Tree")
	{
		test(PointFinder::Method::KDTree);
	}

	SECTION("QuadTree")
	{
		test(PointFinder::Method::QuadTree);
	}
}

TEST_CASE("surrounding a central point")
{
	auto test = [](PointFinder::Method method)
	{
		// Due to the lat/long projection, this is more of an octagon than a square, but
		// that's not a problem for this test case.
		std::vector<CountyRecord> records {
			// corners counter clockwise from quadrant I
			{"Corner", "C1", 9, 9},
			{"Corner", "C2", -9, 9},
			{"Corner", "C3", -9, -9},
			{"Corner", "C4", 9, -9},
			// midpoints counter clockwise from top
			{"Midpoint", "MT", 0, 9},
			{"Midpoint", "ML", -9, 0},
			{"Midpoint", "MB", 0, -9},
			{"Midpoint", "MR", 9, 0},
			// center
			{"Center", "O", 0, 0},
		};

		// KD Tree should split in to left and right halves on the root
		auto finder = PointFinder::Make(method, records);

		SECTION("exact points")
		{
			for (const auto& record : records)
			{
				auto nearest = finder->FindNearest(record.m_latitude, record.m_longitude, 1);
				REQUIRE(nearest.size() == 1);
				REQUIRE(record == nearest.front());
			}
		}

		SECTION("in between")
		{
			auto nearest = finder->FindNearest(1, 1, 1);
			REQUIRE(nearest.size() == 1);
			REQUIRE(records[8] == nearest.front());

			nearest = finder->FindNearest(8, 8, 1);
			REQUIRE(nearest.size() == 1);
			REQUIRE(records[0] == nearest.front());
		}

		SECTION("2 nearest")
		{
			auto nearest = finder->FindNearest(7, 9, 2);
			REQUIRE(nearest.size() == 2);
			CHECK(records[4] == nearest[0]);
			REQUIRE(records[0] == nearest[1]);
		}
	};

	SECTION("KD Tree")
	{
		test(PointFinder::Method::KDTree);
	}

	SECTION("QuadTree")
	{
		test(PointFinder::Method::QuadTree);
	}
}
