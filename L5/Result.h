#ifndef RESULT_H
#define RESULT_H

#include <vector>

// ------------------- KLASA Result<T, E>------------------------------

template <typename T, typename E>
class Result {
public:
    Result(const T& value);
    Result(E* error);
    Result(const std::vector<E*>& errors);
    Result(const Result<T, E>& other);
    ~Result();

    Result<T, E>& operator=(const Result<T, E>& other);

    static Result<T, E> ok(const T& value);
    static Result<T, E> fail(E* error);
    static Result<T, E> fail(const std::vector<E*>& errors);

    // Gettery
    bool isSuccess() const;
    T getValue() const;
    std::vector<E*> getErrors() const;

private:
    T* value;
    std::vector<E*> errors;

    void clear();
};

// ------------------- SPECJALIZACJA Result<void, E>------------------------------
template <typename E>
class Result<void, E> {
public:
    Result();
    Result(E* error);
    Result(const std::vector<E*>& errors);
    Result(const Result<void, E>& other);
    ~Result();

    Result<void, E>& operator=(const Result<void, E>& other);

    static Result<void, E> ok();
    static Result<void, E> fail(E* error);
    static Result<void, E> fail(const std::vector<E*>& errors);

    bool isSuccess() const;
    std::vector<E*> getErrors() const;

private:
    std::vector<E*> errors;

    void clear();
};

// ------------------- IMPLEMENTACJA Result<T, E>------------------------------
// Konstr. sukcesu
template <typename T, typename E>
Result<T, E>::Result(const T& val) {
    value = new T(val);
}

// Konstr. porazki (1 blad)
template <typename T, typename E>
Result<T, E>::Result(E* error) {
    value = nullptr;
    errors.push_back(error);
}

// Konstr. porazki (wiele bledow)
template <typename T, typename E>
Result<T, E>::Result(const std::vector<E*>& errs) {
    value = nullptr;
    errors = errs;
}

// Konstr. kopiujacy
template <typename T, typename E>
Result<T, E>::Result(const Result<T, E>& other) {
    if (other.value != nullptr) {
        value = new T(*other.value);
    } else {
        value = nullptr;
    }
    for (size_t i = 0; i < other.errors.size(); ++i) {
        errors.push_back(other.errors[i]->clone());
    }
}

// Destruktor
template <typename T, typename E>
Result<T, E>::~Result() {
    clear();
}

// Metoda czyszczaca
template <typename T, typename E>
void Result<T, E>::clear() {
    if (value) {
        delete value;
        value = nullptr;
    }
    for (size_t i = 0; i < errors.size(); ++i) {
        delete errors[i];
    }
    errors.clear();
}

// Operator przypisania
template <typename T, typename E>
Result<T, E>& Result<T, E>::operator=(const Result<T, E>& other) {
    if (this != &other) {
        clear();
        if (other.value) {
            value = new T(*other.value);
        }
        for (size_t i = 0; i < other.errors.size(); ++i) {
            errors.push_back(other.errors[i]->clone());
        }
    }
    return *this;
}

// Metody statyczne
template <typename T, typename E>
Result<T, E> Result<T, E>::ok(const T& val) {
    return Result<T, E>(val);
}

template <typename T, typename E>
Result<T, E> Result<T, E>::fail(E* error) {
    return Result<T, E>(error);
}

template <typename T, typename E>
Result<T, E> Result<T, E>::fail(const std::vector<E*>& errors) {
    return Result<T, E>(errors);
}

// Gettery
template <typename T, typename E>
bool Result<T, E>::isSuccess() const {
    return errors.empty();
}

template <typename T, typename E>
T Result<T, E>::getValue() const {
    if (value) return *value;
    return T();
}

template <typename T, typename E>
std::vector<E*> Result<T, E>::getErrors() const {
    return errors;
}







// ------------------- MODYFIKACJA------------------------------
template <typename T>
class Result<T, T>;











// ------------------- IMPLEMENTACJA Result<void, E>------------------------------

// Konstruktory
template <typename E>
Result<void, E>::Result() {
}

template <typename E>
Result<void, E>::Result(E* error) {
    errors.push_back(error);
}

template <typename E>
Result<void, E>::Result(const std::vector<E*>& errs) {
    errors = errs;
}

template <typename E>
Result<void, E>::Result(const Result<void, E>& other) {
    for (size_t i = 0; i < other.errors.size(); ++i) {
        errors.push_back(other.errors[i]->clone());
    }
}

// Destruktor i czyszczenie
template <typename E>
Result<void, E>::~Result() {
    clear();
}

template <typename E>
void Result<void, E>::clear() {
    for (size_t i = 0; i < errors.size(); ++i) {
        delete errors[i];
    }
    errors.clear();
}

// Operator przypisania
template <typename E>
Result<void, E>& Result<void, E>::operator=(const Result<void, E>& other) {
    if (this != &other) {
        clear();
        for (size_t i = 0; i < other.errors.size(); ++i) {
            errors.push_back(other.errors[i]->clone());
        }
    }
    return *this;
}

// Metody statyczne
template <typename E>
Result<void, E> Result<void, E>::ok() {
    return Result<void, E>();
}

template <typename E>
Result<void, E> Result<void, E>::fail(E* error) {
    return Result<void, E>(error);
}

template <typename E>
Result<void, E> Result<void, E>::fail(const std::vector<E*>& errors) {
    return Result<void, E>(errors);
}

// Gettery
template <typename E>
bool Result<void, E>::isSuccess() const {
    return errors.empty();
}

template <typename E>
std::vector<E*> Result<void, E>::getErrors() const {
    return errors;
}
#endif //RESULT_H