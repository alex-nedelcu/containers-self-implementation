cmake_minimum_required(VERSION 3.19)
project(Assignment_4___MultiMap_on_hash_table)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment_4___MultiMap_on_hash_table
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        MultiMap.cpp
        MultiMap.h
        MultiMapIterator.cpp
        MultiMapIterator.h
        ShortTest.cpp
        ShortTest.h
        Utils.cpp
        Utils.h)
