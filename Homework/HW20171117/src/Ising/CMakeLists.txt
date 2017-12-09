# Cmake file for ISING binary
cmake_minimum_required(VERSION 2.6)
message(STATUS "Change Catalogue to src/Ising")
message(STATUS "Project Source Directory: ${PROJECT_SOURCE_DIR}")
message(STATUS "Project Binary Directory: ${PROJECT_BINARY_DIR}")

set(SOURCES terminal_IO.cpp Ising.cpp ConvergenceMonitor.cpp IsingSimulation.cpp)

include_directories(${PROJECT_SOURCE_DIR}/Ising/Eigen)

add_executable(ISING ${SOURCES})
set_target_properties(ISING 
PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/build")