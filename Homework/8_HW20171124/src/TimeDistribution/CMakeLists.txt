cmake_minimum_required(VERSION 2.6)

set(SOURCE_FILES TimeDistribution.cpp terminal_IO.cpp)

include_directories(${PROJECT_BINARY_DIR}/src/RandomWalk)
include_directories(${PROJECT_BINARY_DIR}/src/MyVector)

link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(TimeDistribution ${SOURCE_FILES})
target_link_libraries(TimeDistribution RandomWalk MyVector)
set_target_properties(TimeDistribution
PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build)