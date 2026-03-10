//
// Created by Kuba Iwanicki on 09/12/2025.
//

#include "Error.h"

Error::Error(std::string message) : message(message) {}

Error::~Error() {}

std::string Error::getMessage() const {
    return message;
}

Error* Error::clone() const {
    return new Error(*this);
}


