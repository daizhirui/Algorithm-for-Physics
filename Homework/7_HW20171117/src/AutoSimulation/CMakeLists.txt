# Cmake file for ISING binary
cmake_minimum_required(VERSION 2.6)
message(STATUS "Change Catalogue to src")
message(STATUS "Project Source Directory: ${PROJECT_SOURCE_DIR}")
message(STATUS "Project Binary Directory: ${PROJECT_BINARY_DIR}")

set(SOURCES AutoSimulation.cpp terminal_IO.cpp)


add_executable(AutoSimulation ${SOURCES})
set_target_properties(AutoSimulation
PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/build")