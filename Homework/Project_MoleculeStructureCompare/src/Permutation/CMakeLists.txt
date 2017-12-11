cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_STANDARD 11)

set(LIB_NAME Permutation)
set(LIB_SOURCE_FILES Permutation.cpp)

add_library(${LIB_NAME} ${LIB_SOURCE_FILES})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

link_directories(${PROJECT_BINARY_DIR}/lib)
add_executable(testPermutation testPermutation.cpp)
target_link_libraries(testPermutation ${LIB_NAME})
set_target_properties(testPermutation
PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build)
