cmake_minimum_required(VERSION 2.6)

add_subdirectory(MyVector)

include_directories(${PROJECT_BINARY_DIR}/src/MyVector)

set(SOURCE_FILES Particle.cpp terminal_IO.cpp SingleBrown.cpp)

link_directories(${PROJECT_BINARY_DIR}/lib)
link_libraries(MyVector)

add_executable(SingleBrown ${SOURCE_FILES})
set_target_properties(SingleBrown
PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build)