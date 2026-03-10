//
// Created by Kuba Iwanicki on 23/11/2025.
//

#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <string>
#include <vector>

class Tree {
public:
    Tree();
    ~Tree();
    Tree(const Tree& other);
    Tree& operator=(const Tree& other);
    Tree operator+(const Tree& other) const;

    void enter(const std::string& formula);
    void join(const std::string& formula);
    void print() const;
    std::vector<std::string> getVars() const;
    double calculate(const std::vector<double>& values) const;

private:
    Node* root;
    std::vector<std::string> tokenize(const std::string& text);
};

#endif//TREE_H
