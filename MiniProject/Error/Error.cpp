//
// Created by Kuba Iwanicki on 28/01/2026.
//

#include "Error.h"

Error::Error() : message("Unknown error"){}

Error::Error(const std::string &message) : message(message){}

Error::Error(const Error &other) : message(other.message){}

Error &Error::operator=(const Error &other) {
    if (this != &other) {
        this->message = other.message;
    }
    return *this;
}

Error::~Error() = default;

std::string Error::getMessage() const {
    return message;
}
