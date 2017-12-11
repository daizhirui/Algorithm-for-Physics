cmake_minimum_required(VERSION 2.6)

set(LIB_NAME RandomWalk)

set(SOURCE_FILES RandomWalk.cpp)
set(HEADER_FILES RandomWalk.h)

include_directories(${PROJECT_BINARY_DIR}/src/MyVector)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${LIN_NAME} MyVector)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_executable(testRandomWalk testRandomWalk.cpp)
target_link_libraries(testRandomWalk RandomWalk MyVector)
set_target_properties(testRandomWalk
PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build)