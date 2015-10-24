cmake_minimum_required(VERSION 3.3)
project(compprogcheatsheet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

set(SOURCE_FILES
        code/binary-search/test/binary-search-test1.cpp)

add_executable(compprogcheatsheet ${SOURCE_FILES})