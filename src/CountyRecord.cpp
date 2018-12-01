#include "CountyRecord.h"

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
