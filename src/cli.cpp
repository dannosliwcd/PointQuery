#include <CountyRecord.h>
#include <PointFinder.h>
#include <CLI11.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>
#include <memory>
#include <limits>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char** argv)
{
	static const std::string METHOD_LINEAR("linear");
	static const std::string METHOD_QUADTREE("quadtree");
	static const std::string METHOD_KD_TREE("kdtree");

	CLI::App app("County Search");
	std::string filePath;
	std::vector<std::string> queries;
	std::string methodStr(METHOD_LINEAR);
	unsigned int pointCount = 1;

	app.add_option("county_file", filePath, "Path to file")->required();
	app.add_option("-f,--find", queries, "Queries in latitude:longitude format. E.g. 36.4:-94.4");
	std::ostringstream methodHelp;
	methodHelp << "Search method. May be one of: " << METHOD_LINEAR << " (default), " << METHOD_QUADTREE << ", " << METHOD_KD_TREE;
	app.add_option("-m,--method", methodStr, methodHelp.str());
	app.add_option("-k,--point-count", pointCount, "Number of neighboring points to find per query. Default: 1");
	CLI11_PARSE(app, argc, argv);

	std::ifstream countyFile(filePath);
	if (!countyFile)
	{
		std::cerr << "Unable to open " << filePath << " Error: " << strerror(errno) << std::endl;
		exit(1);
	}

	std::string line;
	if (std::getline(countyFile, line))
	{
		if (!CountyRecord::IsValidHeader(line))
		{
			std::cerr << "Invalid header in " << filePath << std::endl;
			exit(1);
		}
	}
	else
	{
		std::cerr << "Cannot read the first line in " << filePath << std::endl;
		exit(1);
	}

	std::vector<CountyRecord> records;
	while (std::getline(countyFile, line))
	{
		records.emplace_back(CountyRecord::FromString(line));
	}

	PointFinder::Method method;
	if (methodStr == METHOD_LINEAR)
	{
		method = PointFinder::Method::Linear;
	}
	else if (methodStr == METHOD_QUADTREE)
	{
		method = PointFinder::Method::QuadTree;
	}
	else if (methodStr == METHOD_KD_TREE)
	{
		method = PointFinder::Method::KDTree;
	}
	else
	{
		std::cerr << "No such method: " << methodStr << std::endl;
		exit(1);
	}

	auto pointFinder = PointFinder::Make(method, records);
	for (const auto& query : queries)
	{
		auto delimeterIndex = query.find(":");
		decltype(CountyRecord::m_latitude) latitude;
		decltype(CountyRecord::m_longitude) longitude;

		std::istringstream iss(query);
		iss >> latitude;
		iss.ignore(std::numeric_limits<std::streamsize>::max(), ':');
		iss >> longitude;
		std::cout << "Query: " << latitude << ", " << longitude << std::endl;

		if (iss.fail())
		{
			std::cerr << "Query \"" << query << "\" is in an invalid format.\n"
				"Expected: latitude_float:longitude_float." << std::endl;
		}

		auto nearestPoints = pointFinder->FindNearest(latitude, longitude, pointCount);

		std::cout << "Nearest " << pointCount << " points to ("
			<< latitude << ", " << longitude << "):\n";
		for (const auto& point : nearestPoints)
		{
			std::cout << point.m_county << ", " << point.m_state << " (" 
				<< point.m_latitude << ", " << point.m_longitude << ")\n";
		}
		std::cout << std::flush;
	}

	return 0;
}
