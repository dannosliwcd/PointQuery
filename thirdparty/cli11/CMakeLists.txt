project(CLI11 VERSION 1.6.2)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.7")
    # Earlier versions don't completely implement C++11, and are missing functions that this library uses
    message(FATAL_ERROR "GCC must be version 4.7+. Currently have ${CMAKE_CXX_COMPILER_VERSION}")
  endif()
endif()

# CLI11 is a header-only library
# Note: License information is embedded at the top of the header
add_library(cli11 INTERFACE)

target_include_directories(cli11 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)