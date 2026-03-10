#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include "Result.h" // Include Result
#include "Error.h"
#include <string>
#include <vector>
#include <iostream>

class Tree {
public:
    Tree();
    ~Tree();
    Tree(const Tree& other);
    Tree& operator=(const Tree& other);
    Tree operator+(const Tree& other) const;

    void enter(const std::string& formula);

    static Result<Tree*, Error> createTree(const std::string& formula);

    void join(const std::string& formula);
    void print(std::ostream& os = std::cout) const;
    std::vector<std::string> getVars() const;
    double calculate(const std::vector<double>& values) const;

private:
    Node* root;
    static std::vector<std::string> tokenize(const std::string& text);
};

#endif //TREE_H