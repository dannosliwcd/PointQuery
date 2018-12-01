#ifndef COUNTYRECORD_H
#define COUNTYRECORD_H

#include <string>

struct CountyRecord
{
	std::string m_state;
	std::string m_county;
	float m_latitude;
	float m_longitude;

	static CountyRecord FromString(const std::string& countyRecordString);
	static bool IsValidHeader(const std::string& countyRecordString);
};


#endif //COUNTYRECORD_H
