# Effective Programming Techniques (TEP)
This repository contains a collection of academic projects and exercises for the Techniques of Effective Programming course at Wrocław University of Science and Technology. The curriculum focuses on advanced memory management, the mechanics of C++, and heuristic optimization, moving from manual resource control in C++98 to modern move semantics.

**List 1: Memory Allocation and Pointer Basics**
---
The first set of exercises introduces the core distinction between static allocation on the stack and dynamic allocation on the heap. You will find implementations for manual memory management using new and delete operators, including the creation of one-dimensional and multi-dimensional arrays where rows can have varying lengths. A significant part of this list is the development of the Table class, which serves as a sandbox for mastering constructors (default, parameterized, and copy) and the critical role of the destructor in preventing memory leaks.

**List 2: Operator Overloading and Big Numbers**
---
This section explores how to make custom objects as intuitive to use as primitive types through operator overloading. The main project is the Number class, which handles arbitrarily large integers by storing digits in dynamic arrays. It demonstrates the implementation of arithmetic operators such as addition, subtraction, multiplication, and division, as well as the assignment operator. Key lessons here involve handling deep copies and ensuring that objects can be safely assigned to one another without causing dangling pointers or memory corruption.

**List 3: Prefix Expression Trees**
---
The third module focuses on building a mathematical parser that interprets formulas written in prefix (Polish) notation. The program constructs a tree structure where each node represents an operator, variable, or constant. This project includes a robust "repair" mechanism that automatically fixes incomplete expressions by adding default values. It also features tree merging, implemented via the + operator, which grafts one tree onto the leaf of another.

**List 5: Smart Pointers and Move Semantics**
---
Transitioning to the C++11 standard and above, this list introduces smart pointers to automate the deletion of dynamic resources. You will find a custom SmartPointer implementation that uses a reference counter to track object ownership and perform cleanup only when necessary. Additionally, this section covers move semantics, utilizing move constructors and move assignment operators to transfer resources from temporary objects. This significantly optimizes performance by eliminating unnecessary deep copies during data returns and object assignments.

**Mini-Project: Genetic Algorithm (LcVRP)**
---
The capstone of the repository is an optimizer based on the principles of Genetic Algorithms (AG). This project solves the Limited Capacitated Vehicle Routing Problem (LcVRP) by evolving a population of solutions. The architecture consists of a CGeneticAlgorithm class that orchestrates the evolutionary loop, CIndividual objects that handle crossover and mutation of genotypes, and a CEvaluator that calculates the fitness of solutions based on problem-specific constraints
