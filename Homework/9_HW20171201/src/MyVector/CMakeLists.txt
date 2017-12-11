cmake_minimum_required(VERSION 2.6)
# Set Compiler Parameters
set(CMAKE_BUILE_TYPE DEBUG)             # Build Type, DEBUG or RELEASE
set(CMAKE_C_FLAGS_DEBUG "-g -Wall")     # C++ Debug Flags
set(CMAKE_C_FLAGS "-Wall")              # C Flags
set(CMAKE_CXX_FLAGS_DEBUG "--std=c++11 -g -Wall")   # C++ Debug Flags
set(CMAKE_CXX_FLAGS "--std=c++11 -Wall")            # C++ Flags

set(CMAKE_CXX_STANDARD 11)
set(LIB_NAME MyVector)

set(SOURCE_FILES MyVector.cpp)
set(HEADER_FILES MyVector.h)

link_directories(${PROJECT_BINARY_DIR}/lib)

add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_executable(testMyVector testMyVector.cpp)
target_link_libraries(testMyVector MyVector)
set_target_properties(testMyVector
PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build)
