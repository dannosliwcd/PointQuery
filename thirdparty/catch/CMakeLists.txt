project(Catch VERSION 2.5.0)

add_library(catch INTERFACE)

target_include_directories(catch INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
