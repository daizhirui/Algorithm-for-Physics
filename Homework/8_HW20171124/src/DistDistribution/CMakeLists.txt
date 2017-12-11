cmake_minimum_required(VERSION 2.6)

set(SOURCE_FILES terminal_IO.cpp DistDistribution.cpp)

include_directories(${PROJECT_BINARY_DIR}/src/RandomWalk)
include_directories(${PROJECT_BINARY_DIR}/src/MyVector)

link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(DistDistribution ${SOURCE_FILES})
target_link_libraries(DistDistribution RandomWalk MyVector)
set_target_properties(DistDistribution
PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build)