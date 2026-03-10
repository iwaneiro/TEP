cmake_minimum_required(VERSION 4.0)
project(L4)

set(CMAKE_CXX_STANDARD 98)

add_executable(L4
        Error.cpp
        Error.h
        Result.h
        Node.cpp
        Node.h
        Tree.cpp
        Tree.h
        main.cpp
        FileSaver.cpp
        FileSaver.h
)
