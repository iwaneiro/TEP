cmake_minimum_required(VERSION 4.0)
project(LAB6)

set(CMAKE_CXX_STANDARD 14)

add_executable(LAB6 main.cpp
        SmartPtr.h
        RandomUtils.h
        Evaluator/Evaluator.cpp
        Evaluator/Evaluator.h
        Individual/Individual.cpp
        Individual/Individual.h
        GeneticAlgorithm/GeneticAlgorithm.cpp
        GeneticAlgorithm/GeneticAlgorithm.h
        Problem/Problem.cpp
        Problem/Problem.h
        Error/Error.cpp
        Error/Error.h
        Result.h
        )
