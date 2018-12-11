#include "CountyRecord.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

void CountyRecord::CheckValidHeader(const std::string& countyRecordString)
{
	// Example: STATE_ALPHA 	COUNTY_NAME P	RIM_LAT_DEC 	PRIM_LONG_DEC
	std::istringstream iss(countyRecordString);
	std::string column;
	iss >> column;
	if (column != "STATE_ALPHA")
	{
		throw std::runtime_error("Bad column: " + column);
	}
	iss >> column;
	if (column != "COUNTY_NAME")
	{
		throw std::runtime_error("Bad column: " + column);
	}
	iss >> column;
	if (column != "PRIM_LAT_DEC")
	{
		throw std::runtime_error("Bad column: " + column);
	}
	iss >> column;
	if (column != "PRIM_LONG_DEC")
	{
		throw std::runtime_error("Bad column: " + column);
	}
	iss >> column;
	if (!iss.eof())
	{
		throw std::runtime_error("Too many columns");
	}
}

CountyRecord CountyRecord::FromString(const std::string& countyRecordString)
{
	// Example: AR 			Benton 			36.4805825 	-94.4580681
	std::istringstream iss(countyRecordString);
	std::string state;
	std::string county;
	float latitude;
	float longitude;

	std::getline(iss, state, '\t');
	std::getline(iss, county, '\t');
	iss >> latitude >> longitude;
	if (iss.fail())
	{
		throw std::runtime_error("Bad record: " + countyRecordString);
	}
	return {state, county, latitude, longitude};
}

bool operator==(const CountyRecord& lhs, const CountyRecord& rhs)
{
	return lhs.m_state == rhs.m_state
		&& lhs.m_county == rhs.m_county
		&& lhs.m_latitude == rhs.m_latitude
		&& lhs.m_longitude == rhs.m_longitude;
}

bool operator!=(const CountyRecord& lhs, const CountyRecord& rhs) 
{
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const CountyRecord& record)
{
	return os << "[" << record.m_county << ", " <<record.m_state << ", ("
	       	<< record.m_latitude << ", " << record.m_longitude << ")]";
}
