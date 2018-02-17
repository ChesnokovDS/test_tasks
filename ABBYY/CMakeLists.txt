cmake_minimum_required(VERSION 3.9)
project(ABBYY)

set(CMAKE_CXX_STANDARD 17)

add_executable(ABBYY main.cpp Shape.h ShapeStorage.cpp ShapeStorage.h Shape.cpp)