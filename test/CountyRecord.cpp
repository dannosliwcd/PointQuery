#include <CountyRecord.h>
#include <catch.hpp>
#include <string>

TEST_CASE("read a record")
{

	auto record = CountyRecord::FromString("AR	Benton	36.4805825	-94.4580681\n");
	REQUIRE(record.m_state == "AR");
	REQUIRE(record.m_county == "Benton");
	REQUIRE(record.m_latitude == Approx(36.4805825));
	REQUIRE(record.m_longitude == Approx(-94.4580681));
}

TEST_CASE("fail to read an incomplete record")
{
	REQUIRE_THROWS(CountyRecord::FromString("AR"));
}

TEST_CASE("verify a good header")
{
	CountyRecord::CheckValidHeader("STATE_ALPHA	COUNTY_NAME	PRIM_LAT_DEC	PRIM_LONG_DEC\n");
}

TEST_CASE("fail to verify an incomplete header")
{
	REQUIRE_THROWS(CountyRecord::CheckValidHeader("STATE_ALPHA	COUNTY_NAME"));
}
