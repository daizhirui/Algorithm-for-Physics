cmake_minimum_required(VERSION 2.6)

add_subdirectory(Permutation)
add_subdirectory(Combination)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp terminal_IO.cpp StructComp.cpp)
set(LIB Permutation Combination)
link_directories(${PROJECT_BINARY_DIR}/lib)
add_executable(StructCompare ${SOURCE_FILES})
target_link_libraries(StructCompare ${LIB})
set_target_properties(StructCompare
PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build)
