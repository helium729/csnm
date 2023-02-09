#set cmake version
cmake_minimum_required(VERSION 3.0)

#set project name
project(csnm)

#set c++ version
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set source files
aux_source_directory(src SRC_LIST)

#set include directories
include_directories(include)

#set executable
add_executable(${PROJECT_NAME} ${SRC_LIST})