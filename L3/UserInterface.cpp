//
// Created by Kuba Iwanicki on 23/11/2025.
//

#include "UserInterface.h"
#include <iostream>
#include <sstream>
#include <cstdlib>

void UserInterface::run() {
    std::string line, command, args;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        if (line.empty()) continue;

        int spacePos = line.find(' ');
        if (spacePos != std::string::npos) {
            command = line.substr(0, spacePos);
            args = line.substr(spacePos + 1);
        } else {
            command = line;
            args = "";
        }

        if (command == "exit") break;
        handleCommand(command, args);
    }
}

void UserInterface::handleCommand(const std::string& command, const std::string& args) {
    if (command == "enter") {
        tree.enter(args);
        std::cout << "Formula: ";
        tree.print();
    } else if (command == "vars") {
        std::vector<std::string> vars = tree.getVars();
        for (int i = 0; i < vars.size(); i++) std::cout << vars[i] << " ";
        std::cout << std::endl;
    } else if (command == "print") {
        tree.print();
    } else if (command == "comp") {
        std::vector<double> values;
        std::stringstream ss(args);
        std::string temp;
        while (ss >> temp) values.push_back(std::atof(temp.c_str()));
        std::cout << "Result: " << tree.calculate(values) << std::endl;
    } else if (command == "join") {
        tree.join(args);
        std::cout << "Joined. Formula: ";
        tree.print();
    } else {
        std::cout << "Unknown command." << std::endl;
    }
}