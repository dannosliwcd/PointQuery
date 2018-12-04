Project(PointQueryTests)

add_executable(point_query_tests 
	TestRunner.cpp
	CountyRecord.cpp
	PointFinder.cpp
	)
target_link_libraries(point_query_tests PRIVATE PointQuery catch)

catch_discover_tests(point_query_tests)

