cmake_minimum_required(VERSION 3.10)
project(PointCloudProcessing)

find_package(PCL 1.8 REQUIRED)
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES})

include_directories(${PCL_INCLUDE_DIRS})