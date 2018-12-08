#include "CountyRecord.h"
#include <iostream>

bool CountyRecord::IsValidHeader(const std::string& countyRecordString)
{
	// TODO: return whether the given line is a valid header
	// Example: STATE_ALPHA 	COUNTY_NAME P	RIM_LAT_DEC 	PRIM_LONG_DEC
	return false;
}

CountyRecord CountyRecord::FromString(const std::string& countyRecordString)
{
	// TODO: Throw if invalid format
	// TODO: Throw if nothing remaining to read
	// TODO: Read a line of values into a CountyRecord and return it
	// Example: AR 			Benton 			36.4805825 	-94.4580681
	return {};
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
