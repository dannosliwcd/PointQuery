#include "CountyRecord.h"
#include "PointFinder.h"
#include "MaxHeap.h"
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
#include <exception>
#include <chrono>
#include <tuple>

static const unsigned int COUNTY_KNN_COUNT(5);

int main(int argc, char** argv)
{
	auto start = std::chrono::steady_clock::now();
	static const std::string METHOD_HEAP("heap");
	static const std::string METHOD_QUADTREE("quadtree");
	static const std::string METHOD_KD_TREE("kdtree");

	CLI::App app("County Search");
	std::string filePath;
	std::vector<std::string> queries;
	std::string methodStr(METHOD_HEAP);
	unsigned int pointCount = 1;
	bool showCounty = false;

	app.add_option("county_file", filePath, "Path to file")->required();
	app.add_option("-f,--find", queries, "Queries in latitude:longitude format. E.g. 36.4:-94.4");
	std::ostringstream methodHelp;
	methodHelp << "Search method. May be one of: " << METHOD_HEAP << " (default), " << METHOD_QUADTREE << ", " << METHOD_KD_TREE;
	app.add_option("-m,--method", methodStr, methodHelp.str());
	app.add_option("-k,--point-count", pointCount, "Number of neighboring points to find per query. Default: 1");
	app.add_option("-s,--show-surrounding-county", showCounty, "If enabled, also search for the 5 nearest "
			"counties. Print the most common county, state pair in the surrounding area.");
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
		try
		{
			CountyRecord::CheckValidHeader(line);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Bad Header: " << e.what() << std::endl;
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
		if (records.back().m_longitude < 0)
		{
			records.back().m_longitude += 360.0f;
		}
	}

	PointFinder::Method method;
	if (methodStr == METHOD_HEAP)
	{
		method = PointFinder::Method::Heap;
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

	auto buildStart = std::chrono::steady_clock::now();
	auto pointFinder = PointFinder::Make(method, records);
	auto buildEnd = std::chrono::steady_clock::now();
	auto buildElapsed = std::chrono::duration<float>(buildEnd - buildStart);
	std::cout << "Time to build the index: " << buildElapsed.count() << " s\n" << std::endl;
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

		auto knnStart = std::chrono::steady_clock::now();
		auto nearestPoints = pointFinder->FindNearest(
				latitude,
			       	longitude < 0 ? longitude + 360.0f : longitude,
			       	pointCount);
		auto knnEnd = std::chrono::steady_clock::now();
		auto knnElapsed = std::chrono::duration<float>(knnEnd - knnStart);

		std::cout << "Nearest " << pointCount << " points to ("
			<< latitude << ", " << longitude << "):\n";
		for (const auto& point : nearestPoints)
		{
			std::cout << point.m_county << ", " << point.m_state << " (" 
				<< point.m_latitude << ", " << (point.m_longitude > 180 ? point.m_longitude - 360.0f : point.m_longitude) << ")\n";
		}

		std::cout << "Time to calculate nearest neighbors: " << knnElapsed.count() << " s\n" << std::endl;

		if (showCounty)
		{
			// Perform the mode county lookup separately instead of building it in to the requested knn search
			// so we can measure the time for k less than the county lookup count.
			auto countyStart = std::chrono::steady_clock::now();
			auto countyPoints = pointFinder->FindNearest(
					latitude,
					longitude < 0 ? longitude + 360.0f : longitude,
					COUNTY_KNN_COUNT);
			std::vector<std::pair<CountyRecord, unsigned>> countyCounts;
			while (!countyPoints.empty())
			{
				bool found = false;
				const auto& countyPoint = countyPoints.back();
				for (auto& countyCount : countyCounts)
				{
					if (countyCount.first.m_county == countyPoint.m_county
							&& countyCount.first.m_state == countyPoint.m_state)
					{
						countyCount.second += 1;
						found = true;
					}
				}
				if (!found)
				{
					countyCounts.emplace_back(countyPoint, 1);
				}
				countyPoints.pop_back();
			}

			MaxHeap<unsigned, CountyRecord> orderedCountyCounts(countyCounts.size());
			for (const auto& countyCount : countyCounts)
			{
				orderedCountyCounts.Insert(countyCount.second, countyCount.first);
			}

			const auto& selectedCounty = orderedCountyCounts.GetMax().e;
			std::cout << "Point is most likely in \"" << selectedCounty.m_county << "\" county, \""
				<< selectedCounty.m_state << "\" state" << std::endl;

			auto countyEnd = std::chrono::steady_clock::now();
			auto countyElapsed = std::chrono::duration<float>(countyEnd - countyStart);
			std::cout << "Time to select county: " << knnElapsed.count() << " s\n\n" << std::endl;
		}
		
		std::cout << std::flush;
	}
	auto end = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration<float>(end - start);
	std::cout << "Total time in main(): " << elapsed.count() << " s" << std::endl;

	return 0;
}
