#ifndef COUNTYRECORD_H
#define COUNTYRECORD_H

#include <string>
#include <iosfwd>

struct CountyRecord
{
	std::string m_state;
	std::string m_county;
	float m_latitude;
	float m_longitude;

	static CountyRecord FromString(const std::string& countyRecordString);
	static void CheckValidHeader(const std::string& countyRecordString);
};

bool operator==(const CountyRecord& lhs, const CountyRecord& rhs);
bool operator!=(const CountyRecord& lhs, const CountyRecord& rhs);
std::ostream& operator<<(std::ostream& os, const CountyRecord& record);

#endif //COUNTYRECORD_H
