cmake_minimum_required(VERSION 3.10)
project(radar)

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找PCL和VTK
find_package(PCL 1.10 REQUIRED COMPONENTS common io visualization)
find_package(VTK REQUIRED)

# 包含PCL和VTK的头文件目录
include_directories(
    ${PCL_INCLUDE_DIRS}
    ${VTK_INCLUDE_DIRS}
)

# 添加可执行文件
add_executable(radar src/radar.cpp)

# 链接库
target_link_libraries(radar
    ${PCL_LIBRARIES}
    ${VTK_LIBRARIES}
)