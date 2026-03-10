#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include "Error.h"
#include "Result.h"

enum NodeType {
    typeOperator,
    typeConstant,
    typeVariable,
};

class Node {
public:
    Node();
    Node(const std::string& val);
    ~Node();
    Node(const Node& other);

    void build(const std::vector<std::string>& tokens, int& offset, std::vector<Error*>& errors);


    void printPrefix(std::ostream& os = std::cout) const;

    void getVars(std::set<std::string>& vars) const;

    double calculate(const std::map<std::string, double> &varValues) const;

    Node* clone() const;
    bool replaceLeaf(Node* newSubTree);

private:
    std::string value;
    NodeType type;
    std::vector<Node*> children;

    void determineType();
    int getRequiredArgs() const;
};

#endif //NODE_H