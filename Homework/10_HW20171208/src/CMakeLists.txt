cmake_minimum_required(VERSION 2.6)

add_subdirectory(MyVector)

link_directories(${PROJECT_BINARY_DIR}/lib)

set(SOURCE_FILES AtomGroup.cpp Interaction.cpp pdbAnalyser.cpp terminal_IO.cpp main.cpp)

add_executable(MoleculeSystemInterface ${SOURCE_FILES})
target_link_libraries(MoleculeSystemInterface MyVector)
set_target_properties(MoleculeSystemInterface
PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build)