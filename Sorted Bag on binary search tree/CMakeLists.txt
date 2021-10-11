cmake_minimum_required(VERSION 3.19)
project(Assignment_5___SortedBag_on_Binary_Search_Tree)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment_5___SortedBag_on_Binary_Search_Tree
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SortedBag.cpp
        SortedBag.h
        SortedBagIterator.cpp
        SortedBagIterator.h)
