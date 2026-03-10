//
// Created by Kuba Iwanicki on 23/11/2025.
//

#include "Node.h"
#include <iostream>

bool isNumber(std::string& str) {
    if (str.empty()) return false;
    for (int i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

void fixVariableName(std::string& name) {
    std::string cleanName;
    bool wasModified = false;

    for (int i = 0; i < name.length(); i++) {
        if (std::isalnum(name[i])) {
            cleanName += name[i];
        } else {
            wasModified = true;
        }
    }
    if (wasModified) {
        std::cout << "Warn: Fixed invalid char in variable '" << name << "'"<< std::endl;
        name = cleanName;
    }
}

const std::string DEFAULT_VAL = "1";

Node::Node() {
    type = typeConstant;
}

Node::Node(const std::string &val) {
    type = typeConstant;
    value = val;
}

Node::~Node() {
    for (int i = 0; i<children.size(); i++) {
        delete children[i];
    }
    children.clear();
}

Node::Node(const Node &other) {
    value = other.value;
    type = other.type;

    for (int i = 0; i<other.children.size(); i++) {
        new Node(*other.children[i]);
        children.push_back(new Node(*other.children[i]));
    }
}


Node* Node::clone() const {
    return new Node(*this);
}

void Node::build(const std::vector<std::string>& tokens, int& offset) {
    // Brak argumentow - domyslna warosc
    if (offset >= (int)tokens.size()) {
        std::cout<<"Info: Missing argument. Used default value (1)."<<std::endl;
        value = DEFAULT_VAL;
        type = typeConstant;
        return;
    }

    value = tokens[offset];
    offset++;

    determineType();
    int requiredArgs = getRequiredArgs();

    for (int i = 0; i<requiredArgs; i++) {
        Node* child = new Node();
        child->build(tokens, offset);
        children.push_back(child);
    }
}

void Node::printPrefix() const {
    std::cout << value << " ";
    for (int i = 0; i<children.size(); i++) {
        children[i]->printPrefix();
    }
}

void Node::getVars(std::set<std::string>& vars) const {
    if (type == typeVariable) {
        vars.insert(value);
    }
    for (int i = 0; i<children.size(); i++) {
        children[i]->getVars(vars);
    }
}

double Node::calculate(const std::map<std::string, double> &varValues) const {
    if (type == typeConstant) return std::atof(value.c_str());
    if (type == typeVariable) {
        if (varValues.find(value) != varValues.end()) {
            return varValues.find(value)->second;
        }
        return 0.0;
    }

    double v1 = (!children.empty()) ? children[0]->calculate(varValues) : 0.0;
    double v2 = (children.size()>1) ? children[1]->calculate(varValues) : 0.0;

    if (value == "+") return (v1+v2);
    if (value == "-") return (v1-v2);
    if (value == "*") return (v1*v2);
    if (value == "/") return (v2 != 0) ? (v1/v2) : (std::cout<<"Cannot divide by zero."<<std::endl, 0.0);
    if (value == "sin") return (std::sin(v1));
    if (value == "cos") return (std::cos(v1));

    return 0.0;
}


bool Node::replaceLeaf(Node* newSubTree) {
    if (children.empty()) {
        value = newSubTree->value;
        type = newSubTree->type;

        children = newSubTree->children;
        newSubTree->children.clear();
        return true;
    }

    for (int i = 0; i < children.size(); i++) {
        if (children[i]->replaceLeaf(newSubTree)) {
            return true;
        }
    }
    return false;
}


void Node::determineType() {
    if (value == "+" || value == "-" || value == "*" || value == "/" ||
        value == "sin" || value == "cos") {
        type = typeOperator;
    } else if (isNumber(value)) {
        type = typeConstant;
    } else {
        std::string original = value;
        fixVariableName(value);

        // Sprawdzenie czy po naprawie powstala liczba
        if (isNumber(value)) {
            type = typeConstant;
            std::cout << "Warn: Number converted from: "
                      << original << " to: " << value << std::endl;
        } else if (value.empty()) {
            // Pusty ciag - wartosc domyslna
            value = DEFAULT_VAL;
            type = typeConstant;
            std::cout << "Warn: Invalid token: " << original
                      << ". Replaced with default value." << std::endl;
        } else {
            // Jeśli  nie  liczba - to zmienna
            type = typeVariable;
        }
    }
}

int Node::getRequiredArgs() const {
    if (value == "+" || value == "-" || value == "*" || value == "/") return 2;
    if (value == "sin" || value == "cos") return 1;
    return 0;
}




