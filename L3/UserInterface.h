//
// Created by Kuba Iwanicki on 23/11/2025.
//

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "Tree.h"

class UserInterface {
public:
    void run();

private:
    Tree tree;
    void handleCommand(const std::string& command, const std::string& args);
};

#endif//USER_INTERFACE_H