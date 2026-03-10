//
// Created by Kuba Iwanicki on 28/01/2026.
//

#ifndef LAB6_ERROR_H
#define LAB6_ERROR_H
#include <string>


class Error {
private:
    std::string message;

public:
    Error();
    explicit Error(const std::string& message);
    Error(const Error& other);
    Error& operator=(const Error& other);
    ~Error();
    std::string getMessage() const;

};


#endif //LAB6_ERROR_H