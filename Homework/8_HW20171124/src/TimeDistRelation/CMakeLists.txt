cmake_minimum_required(VERSION 2.6)

set(SOURCE_FILES terminal_IO.cpp TimeDistRelation.cpp)

include_directories(${PROJECT_BINARY_DIR}/src/TimeDistRelation/Eigen)
include_directories(${PROJECT_BINARY_DIR}/src/RandomWalk)
include_directories(${PROJECT_BINARY_DIR}/src/MyVector)

link_directories(${PROJECT_BINARY_DIR}/lib)
#link_libraries(RandomWalk MyVector)

add_executable(TimeDistRelation ${SOURCE_FILES})
target_link_libraries(TimeDistRelation RandomWalk MyVector)
set_target_properties(TimeDistRelation
PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build)