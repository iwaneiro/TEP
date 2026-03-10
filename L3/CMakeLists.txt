cmake_minimum_required(VERSION 4.0)
project(TEP3)

set(CMAKE_CXX_STANDARD 98)

add_executable(TEP3 main.cpp
        Node.cpp
        Node.h
        Tree.cpp
        Tree.h
        UserInterface.cpp
        UserInterface.h)
