cmake_minimum_required(VERSION 2.6)
project(ISING)

# The VERSION Number
set(ISING_VERSION 1)
# Set Directory Parameters
# PROJECT_BINARY_DIR is the DIR where terminal command is executed
set(PROJECT_SOURCE_DIR ${PROJECT_BINARY_DIR}/src)
# Print some messages
message(STATUS "Project:ISING")
message(STATUS "Project Source Directory: ${PROJECT_SOURCE_DIR}")
message(STATUS "Project Binary Directory: ${PROJECT_BINARY_DIR}")

# Set Compiler Parameters
set(CMAKE_BUILE_TYPE DEBUG)             # Build Type, DEBUG or RELEASE
set(CMAKE_C_FLAGS_DEBUG "-g -Wall")     # C++ Debug Flags
set(CMAKE_C_FLAGS "-Wall")              # C Flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")   # C++ Debug Flags
set(CMAKE_CXX_FLAGS "-Wall")            # C++ Flags
set(CMAKE_CXX_STANDARD 11)              # using C++11
# set make VERBOSE = 1
set(CMAKE_VERBOSE_MAKEFILE OFF)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/Ising/Config.h.in"
    "${PROJECT_SOURCE_DIR}/Ising/Config.h"
    )

# set source files
add_subdirectory(src)
