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
include src/CMakeFiles/point_query.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/point_query.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/point_query.dir/flags.make

src/CMakeFiles/point_query.dir/cli.cpp.o: src/CMakeFiles/point_query.dir/flags.make
src/CMakeFiles/point_query.dir/cli.cpp.o: ../src/cli.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/point_query.dir/cli.cpp.o"
	cd /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/src && /usr/bin/c++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/point_query.dir/cli.cpp.o -c /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/src/cli.cpp

src/CMakeFiles/point_query.dir/cli.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/point_query.dir/cli.cpp.i"
	cd /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/src && /usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/src/cli.cpp > CMakeFiles/point_query.dir/cli.cpp.i

src/CMakeFiles/point_query.dir/cli.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/point_query.dir/cli.cpp.s"
	cd /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/src && /usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/src/cli.cpp -o CMakeFiles/point_query.dir/cli.cpp.s

src/CMakeFiles/point_query.dir/cli.cpp.o.requires:

.PHONY : src/CMakeFiles/point_query.dir/cli.cpp.o.requires

src/CMakeFiles/point_query.dir/cli.cpp.o.provides: src/CMakeFiles/point_query.dir/cli.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/point_query.dir/build.make src/CMakeFiles/point_query.dir/cli.cpp.o.provides.build
.PHONY : src/CMakeFiles/point_query.dir/cli.cpp.o.provides

src/CMakeFiles/point_query.dir/cli.cpp.o.provides.build: src/CMakeFiles/point_query.dir/cli.cpp.o


# Object files for target point_query
point_query_OBJECTS = \
"CMakeFiles/point_query.dir/cli.cpp.o"

# External object files for target point_query
point_query_EXTERNAL_OBJECTS =

src/point_query.exe: src/CMakeFiles/point_query.dir/cli.cpp.o
src/point_query.exe: src/CMakeFiles/point_query.dir/build.make
src/point_query.exe: src/libPointQuery.a
src/point_query.exe: src/CMakeFiles/point_query.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable point_query.exe"
	cd /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/point_query.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/point_query.dir/build: src/point_query.exe

.PHONY : src/CMakeFiles/point_query.dir/build

src/CMakeFiles/point_query.dir/requires: src/CMakeFiles/point_query.dir/cli.cpp.o.requires

.PHONY : src/CMakeFiles/point_query.dir/requires

src/CMakeFiles/point_query.dir/clean:
	cd /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/src && $(CMAKE_COMMAND) -P CMakeFiles/point_query.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/point_query.dir/clean

src/CMakeFiles/point_query.dir/depend:
	cd /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/src /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/src /cygdrive/c/Users/Brian/Desktop/EC504/PointQuery/build/src/CMakeFiles/point_query.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/point_query.dir/depend
