# Cmake file for ISING binary
cmake_minimum_required(VERSION 2.6)
message(STATUS "Change Catalogue to src")
message(STATUS "Project Source Directory: ${PROJECT_SOURCE_DIR}")
message(STATUS "Project Binary Directory: ${PROJECT_BINARY_DIR}")

add_subdirectory(${PROJECT_SOURCE_DIR}/Ising)
add_subdirectory(${PROJECT_SOURCE_DIR}/AutoSimulation)
