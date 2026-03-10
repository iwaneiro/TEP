//
// Created by Kuba Iwanicki on 23/11/2025.
//

#include "Tree.h"
#include <iostream>
#include <sstream>

Tree::Tree() : root(nullptr){}

Tree::~Tree() {
    if (root) delete root;
}

Tree::Tree(const Tree &other) {
    if (other.root) root = other.root->clone();
    else root = nullptr;
}

Tree &Tree::operator=(const Tree &other) {
    if (this != &other) {
        if (root) {
            delete root;
            root = nullptr;
        }
        if (other.root) root = other.root->clone();
    }
    return *this;
}

Tree Tree::operator+(const Tree& other) const {
    if (!root) {
        return other;
    }

    Tree result(*this);
    if (result.root && other.root) {
        Node* subTreeCopy = other.root->clone();
        result.root->replaceLeaf(subTreeCopy);
        delete subTreeCopy;
    }
    return result;
}

void Tree::enter(const std::string &formula) {
    if (root) {
        delete root;
        root = nullptr;
    }

    std::vector<std::string> tokens = tokenize(formula);
    if (tokens.empty()) return;

    int offset = 0;
    root = new Node();
    root -> build(tokens, offset);

    if (offset < (int) tokens.size()) {
        std::cout << "Info: Ignored extra tokens." << std::endl;
    }
}

void Tree::join(const std::string &formula) {
    Tree otherTree;
    otherTree.enter(formula);
    *this = *this + otherTree;
}

std::vector<std::string> Tree::getVars() const {
    std::set<std::string> varsSet;
    if (root) root->getVars(varsSet);

    std::vector<std::string> result;
    for (std::set<std::string>::iterator it = varsSet.begin(); it != varsSet.end(); ++it) {
        result.push_back(*it);
    }
    return result;
}

void Tree::print() const {
    if (root) {
        root->printPrefix();
        std::cout<<std::endl;
    }
}

double Tree::calculate(const std::vector<double> &values) const {
    std::vector<std::string> vars = getVars();
    if (values.size() != vars.size()) {
        std::cout << "Error: Value count mismatch. Expected " << vars.size() <<" values."<<std::endl;
        return 0;
    }

    std::map<std::string, double> varMap;
    for (int i = 0; i < vars.size(); i++) {
        varMap[vars[i]] = values[i];
    }
    return root ? root->calculate(varMap) : 0;
}

std::vector<std::string> Tree::tokenize(const std::string& text) {
    std::vector<std::string> tokens;
    std::string current;
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == ' ') {
            if (!current.empty()){
                tokens.push_back(current);
                current = "";
            }
        } else {
            current += text[i];
        }
    }
    if (!current.empty()) tokens.push_back(current);
    return tokens;
}


