# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/daizhirui/Documents/Developments/Algorithm-for-Physics/Homework/HW20171117

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/daizhirui/Documents/Developments/Algorithm-for-Physics/Homework/HW20171117

# Include any dependencies generated for this target.
include src/CMakeFiles/AutoSimulation.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/AutoSimulation.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/AutoSimulation.dir/flags.make

src/CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.o: src/CMakeFiles/AutoSimulation.dir/flags.make
src/CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.o: src/AutoSimulation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/daizhirui/Documents/Developments/Algorithm-for-Physics/Homework/HW20171117/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.o"
	cd /Users/daizhirui/Documents/Developments/Algorithm-for-Physics/Homework/HW20171117/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.o -c /Users/daizhirui/Documents/Developments/Algorithm-for-Physics/Homework/HW20171117/src/AutoSimulation.cpp

src/CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.i"
	cd /Users/daizhirui/Documents/Developments/Algorithm-for-Physics/Homework/HW20171117/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/daizhirui/Documents/Developments/Algorithm-for-Physics/Homework/HW20171117/src/AutoSimulation.cpp > CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.i

src/CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.s"
	cd /Users/daizhirui/Documents/Developments/Algorithm-for-Physics/Homework/HW20171117/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/daizhirui/Documents/Developments/Algorithm-for-Physics/Homework/HW20171117/src/AutoSimulation.cpp -o CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.s

src/CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.o.requires:

.PHONY : src/CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.o.requires

src/CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.o.provides: src/CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/AutoSimulation.dir/build.make src/CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.o.provides.build
.PHONY : src/CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.o.provides

src/CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.o.provides.build: src/CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.o


# Object files for target AutoSimulation
AutoSimulation_OBJECTS = \
"CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.o"

# External object files for target AutoSimulation
AutoSimulation_EXTERNAL_OBJECTS =

build/AutoSimulation: src/CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.o
build/AutoSimulation: src/CMakeFiles/AutoSimulation.dir/build.make
build/AutoSimulation: src/CMakeFiles/AutoSimulation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/daizhirui/Documents/Developments/Algorithm-for-Physics/Homework/HW20171117/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../build/AutoSimulation"
	cd /Users/daizhirui/Documents/Developments/Algorithm-for-Physics/Homework/HW20171117/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AutoSimulation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/AutoSimulation.dir/build: build/AutoSimulation

.PHONY : src/CMakeFiles/AutoSimulation.dir/build

src/CMakeFiles/AutoSimulation.dir/requires: src/CMakeFiles/AutoSimulation.dir/AutoSimulation.cpp.o.requires

.PHONY : src/CMakeFiles/AutoSimulation.dir/requires

src/CMakeFiles/AutoSimulation.dir/clean:
	cd /Users/daizhirui/Documents/Developments/Algorithm-for-Physics/Homework/HW20171117/src && $(CMAKE_COMMAND) -P CMakeFiles/AutoSimulation.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/AutoSimulation.dir/clean

src/CMakeFiles/AutoSimulation.dir/depend:
	cd /Users/daizhirui/Documents/Developments/Algorithm-for-Physics/Homework/HW20171117 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/daizhirui/Documents/Developments/Algorithm-for-Physics/Homework/HW20171117 /Users/daizhirui/Documents/Developments/Algorithm-for-Physics/Homework/HW20171117/src /Users/daizhirui/Documents/Developments/Algorithm-for-Physics/Homework/HW20171117 /Users/daizhirui/Documents/Developments/Algorithm-for-Physics/Homework/HW20171117/src /Users/daizhirui/Documents/Developments/Algorithm-for-Physics/Homework/HW20171117/src/CMakeFiles/AutoSimulation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/AutoSimulation.dir/depend

