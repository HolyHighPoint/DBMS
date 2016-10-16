cmake_minimum_required(VERSION 2.8)
project(DBMS)
include_directories(include)
set(CMAKE_CXX_FLAGS "-g")
#set(CMAKE_CXX_FLAGS "-g -Ofast")
add_executable(DBMS test.cpp)

