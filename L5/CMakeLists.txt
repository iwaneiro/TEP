cmake_minimum_required(VERSION 4.0)
project(L5)

set(CMAKE_CXX_STANDARD 11)

add_executable(L5 main.cpp
        ReferenceCounter.h
        SmartPointer.h
        Error.cpp
        FileSaver.cpp
        Node.cpp
        Tree.cpp
        BorrowingPointer.h
)
