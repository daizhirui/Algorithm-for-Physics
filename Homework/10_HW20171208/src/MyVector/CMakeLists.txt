cmake_minimum_required(VERSION 2.6)

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