//
// Created by Kuba Iwanicki on 28/01/2026.
//

#ifndef LAB6_RESULT_H
#define LAB6_RESULT_H
#include <vector>

#include "SmartPtr.h"


template<typename T, typename E>
class Result {
private:
    SmartPtr<T> value;
    std::vector<SmartPtr<E>> errors;

    explicit Result(T* v) : value(v) {}
    explicit Result(std::vector<SmartPtr<E>>& errs) : value(nullptr), errors(errs) {}
    explicit Result(SmartPtr<E> error) : value(nullptr) { errors.push_back(error); }

public:
    static Result success(const T& val) {
        return Result(new T(val));
    }

    static Result fail(const std::string& msg) {
        return Result(SmartPtr<E>(new E(msg)));
    }

    static Result fail(std::vector<SmartPtr<E>>& errs) {
        return Result(errs);
    }

    bool isSuccess() const {
        return errors.empty();
    }

    T getValue() const {
        if (!value.isNull()) return *value;
        return T();
    }

    std::vector<SmartPtr<E>>& getErrors() {
        return errors;
    }

    std::string getErrorMessage() {
        std::string msg;
        for (size_t i=0; i<errors.size(); i++) {
            msg += errors[i]->getMessage() + "\n";
        }
        return msg;
    }
};

template <typename E>
class Result<void, E> {
private:
    std::vector<SmartPtr<E>> errors;

    Result() {}
    explicit Result(SmartPtr<E> error) { errors.push_back(error); }
    explicit Result(std::vector<SmartPtr<E>>& errs) : errors(errs) {}

public:
    static Result success() {
        return Result();
    }

    static Result fail(const std::string& msg) {
        return Result(SmartPtr<E>(new E(msg)));
    }

    bool isSuccess() const {
        return errors.empty();
    }

    std::vector<SmartPtr<E>>& getErrors() {
        return errors;
    }

    std::string getErrorMessage() {
        std::string msg;
        for (size_t i=0; i<errors.size(); i++) {
            msg += errors[i]->getMessage() + "\n";
        }
        return msg;
    }
};

#endif //LAB6_RESULT_H