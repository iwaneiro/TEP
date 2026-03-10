//
// Created by Kuba Iwanicki on 09/12/2025.
//

#ifndef L4_ERROR_H
#define L4_ERROR_H
#include <string>


class Error {
public:
    Error(std::string message);
    virtual ~Error();
    std::string getMessage() const;

    virtual Error* clone() const;

private:
    std::string message;
};


#endif //L4_ERROR_H