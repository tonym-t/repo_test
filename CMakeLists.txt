# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.0)

#项目名称
project(main)

# set(SOURCE main.cpp test.h test.cpp)
aux_source_directory(. SOURCE)

#dubug 模式
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# 指定生成目标
add_executable(${PROJECT_NAME} ${SOURCE})