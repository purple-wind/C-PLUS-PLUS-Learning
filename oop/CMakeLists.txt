cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0")
project(oop)
add_executable(oop  main.cpp quote.cpp query.cpp)
