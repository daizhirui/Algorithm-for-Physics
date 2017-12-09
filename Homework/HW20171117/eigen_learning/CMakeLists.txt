cmake_minimum_required (VERSION 2.6)
project (eigen_learning)
# The version number
set(eigen_learning_VERSION_MAJOR 1)
set(eigen_learning_VERSION_MINOR 0)

# add eigen header files
include_directories(${PROJECT_SOURCE_DIR}/../../Eigen)


# add the executables
add_executable(practice1 practice1.cpp)
add_executable(practice2 practice2.cpp)
add_executable(practice3 practice3.cpp)
add_executable(practice4 practice4.cpp)
add_executable(practice5 practice5.cpp)
add_executable(practice6 practice6.cpp)
add_executable(practice7 practice7.cpp)
