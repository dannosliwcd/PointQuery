# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake.exe

# The command to remove a file.
RM = /usr/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build

# Include any dependencies generated for this target.
include test/CMakeFiles/point_query_tests.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/point_query_tests.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/point_query_tests.dir/flags.make

test/CMakeFiles/point_query_tests.dir/TestRunner.cpp.o: test/CMakeFiles/point_query_tests.dir/flags.make
test/CMakeFiles/point_query_tests.dir/TestRunner.cpp.o: ../test/TestRunner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/point_query_tests.dir/TestRunner.cpp.o"
	cd /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/test && /usr/bin/c++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/point_query_tests.dir/TestRunner.cpp.o -c /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/test/TestRunner.cpp

test/CMakeFiles/point_query_tests.dir/TestRunner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/point_query_tests.dir/TestRunner.cpp.i"
	cd /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/test && /usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/test/TestRunner.cpp > CMakeFiles/point_query_tests.dir/TestRunner.cpp.i

test/CMakeFiles/point_query_tests.dir/TestRunner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/point_query_tests.dir/TestRunner.cpp.s"
	cd /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/test && /usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/test/TestRunner.cpp -o CMakeFiles/point_query_tests.dir/TestRunner.cpp.s

test/CMakeFiles/point_query_tests.dir/TestRunner.cpp.o.requires:

.PHONY : test/CMakeFiles/point_query_tests.dir/TestRunner.cpp.o.requires

test/CMakeFiles/point_query_tests.dir/TestRunner.cpp.o.provides: test/CMakeFiles/point_query_tests.dir/TestRunner.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/point_query_tests.dir/build.make test/CMakeFiles/point_query_tests.dir/TestRunner.cpp.o.provides.build
.PHONY : test/CMakeFiles/point_query_tests.dir/TestRunner.cpp.o.provides

test/CMakeFiles/point_query_tests.dir/TestRunner.cpp.o.provides.build: test/CMakeFiles/point_query_tests.dir/TestRunner.cpp.o


test/CMakeFiles/point_query_tests.dir/CountyRecord.cpp.o: test/CMakeFiles/point_query_tests.dir/flags.make
test/CMakeFiles/point_query_tests.dir/CountyRecord.cpp.o: ../test/CountyRecord.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/point_query_tests.dir/CountyRecord.cpp.o"
	cd /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/test && /usr/bin/c++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/point_query_tests.dir/CountyRecord.cpp.o -c /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/test/CountyRecord.cpp

test/CMakeFiles/point_query_tests.dir/CountyRecord.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/point_query_tests.dir/CountyRecord.cpp.i"
	cd /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/test && /usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/test/CountyRecord.cpp > CMakeFiles/point_query_tests.dir/CountyRecord.cpp.i

test/CMakeFiles/point_query_tests.dir/CountyRecord.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/point_query_tests.dir/CountyRecord.cpp.s"
	cd /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/test && /usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/test/CountyRecord.cpp -o CMakeFiles/point_query_tests.dir/CountyRecord.cpp.s

test/CMakeFiles/point_query_tests.dir/CountyRecord.cpp.o.requires:

.PHONY : test/CMakeFiles/point_query_tests.dir/CountyRecord.cpp.o.requires

test/CMakeFiles/point_query_tests.dir/CountyRecord.cpp.o.provides: test/CMakeFiles/point_query_tests.dir/CountyRecord.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/point_query_tests.dir/build.make test/CMakeFiles/point_query_tests.dir/CountyRecord.cpp.o.provides.build
.PHONY : test/CMakeFiles/point_query_tests.dir/CountyRecord.cpp.o.provides

test/CMakeFiles/point_query_tests.dir/CountyRecord.cpp.o.provides.build: test/CMakeFiles/point_query_tests.dir/CountyRecord.cpp.o


# Object files for target point_query_tests
point_query_tests_OBJECTS = \
"CMakeFiles/point_query_tests.dir/TestRunner.cpp.o" \
"CMakeFiles/point_query_tests.dir/CountyRecord.cpp.o"

# External object files for target point_query_tests
point_query_tests_EXTERNAL_OBJECTS =

test/point_query_tests.exe: test/CMakeFiles/point_query_tests.dir/TestRunner.cpp.o
test/point_query_tests.exe: test/CMakeFiles/point_query_tests.dir/CountyRecord.cpp.o
test/point_query_tests.exe: test/CMakeFiles/point_query_tests.dir/build.make
test/point_query_tests.exe: src/libPointQuery.a
test/point_query_tests.exe: test/CMakeFiles/point_query_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable point_query_tests.exe"
	cd /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/point_query_tests.dir/link.txt --verbose=$(VERBOSE)
	cd /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/test && /usr/bin/cmake.exe -D TEST_TARGET=point_query_tests -D TEST_EXECUTABLE=/cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/test/point_query_tests.exe -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/test -D TEST_SPEC= -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_LIST=point_query_tests_TESTS -D CTEST_FILE=/cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/test/point_query_tests_tests-b858cb2.cmake -P /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/thirdparty/catch/CatchAddTests.cmake

# Rule to build all files generated by this target.
test/CMakeFiles/point_query_tests.dir/build: test/point_query_tests.exe

.PHONY : test/CMakeFiles/point_query_tests.dir/build

test/CMakeFiles/point_query_tests.dir/requires: test/CMakeFiles/point_query_tests.dir/TestRunner.cpp.o.requires
test/CMakeFiles/point_query_tests.dir/requires: test/CMakeFiles/point_query_tests.dir/CountyRecord.cpp.o.requires

.PHONY : test/CMakeFiles/point_query_tests.dir/requires

test/CMakeFiles/point_query_tests.dir/clean:
	cd /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/test && $(CMAKE_COMMAND) -P CMakeFiles/point_query_tests.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/point_query_tests.dir/clean

test/CMakeFiles/point_query_tests.dir/depend:
	cd /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/test /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/test /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/test/CMakeFiles/point_query_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/point_query_tests.dir/depend
