cmake_minimum_required(VERSION 3.19)
project(Assignment_3___Map_on_SLLA)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment_3___Map_on_SLLA
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        Map.cpp
        Map.h
        MapIterator.cpp
        MapIterator.h
        ShortTest.cpp
        ShortTest.h)
