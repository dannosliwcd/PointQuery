add_library(PointQuery STATIC
	CountyRecord.cpp CountyRecord.h
	PointFinder.cpp PointFinder.h
	KDTreePointFinder.cpp KDTreePointFinder.h
	HeapPointFinder.cpp HeapPointFinder.h
	QuadTreePointFinder.cpp QuadTreePointFinder.h
	MaxHeap.h
	)
target_include_directories(PointQuery PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(point_query cli.cpp)
target_link_libraries(point_query PRIVATE PointQuery cli11)
