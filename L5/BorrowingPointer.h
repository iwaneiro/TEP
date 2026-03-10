

#ifndef L5_BORROWINGPOINTER_H
#define L5_BORROWINGPOINTER_H
#include "ReferenceCounter.h"
template <typename T> class SmartPointer;


template <typename T>
class BorrowingPointer {
    friend class SmartPointer<T>;
public:
    BorrowingPointer()
        : pointer(nullptr),
          counter(nullptr) {}

    BorrowingPointer(const SmartPointer<T> &smartPointer) {
        pointer = smartPointer.pointer;
        counter = smartPointer.counter;
        if (counter) {
            counter -> borrowAdd();
            counter -> addListener((void*)&pointer);
        }
    }

    BorrowingPointer(const BorrowingPointer& other) {
        pointer = other.pointer;
        counter = other.counter;
        if (counter) {
            counter->borrowAdd();
            counter->addListener((void*)&pointer);
        }
    }

    BorrowingPointer& operator=(const BorrowingPointer& other) {
        if (this != &other) {
            release();
            pointer = other.pointer;
            counter = other.counter;
            if (counter) {
                counter->borrowAdd();
                counter->addListener((void*)&pointer);
            }
        }
        return *this;
    }

    ~BorrowingPointer() {
        release();
    }

    BorrowingPointer(BorrowingPointer&& other) noexcept {
        pointer = other.pointer;
        counter = other.counter;

        if (counter) {
            counter->removeListener(&other.pointer);
            counter->addListener(&pointer);
        }

        other.pointer = nullptr;
        other.counter = nullptr;
    }

    BorrowingPointer& operator=(BorrowingPointer&& other) noexcept {
        if (this != &other) {
            release();

            pointer = other.pointer;
            counter = other.counter;

            if (counter) {
                counter->removeListener(&other.pointer);
                counter->addListener(&pointer);
            }

            other.pointer = nullptr;
            other.counter = nullptr;
        }
        return *this;
    }


    T& operator*() {
        if (!pointer) throw std::runtime_error("Accessing null borrowed pointer!");
        return *pointer;
    }

    T* operator->() {
        return pointer;
    }

    T* get() const { return pointer; }

private:
    T* pointer;
    ReferenceCounter* counter;

    void release() {
        if (counter) {
            counter->removeListener((void*)&pointer);

            if (counter->borrowDec() == 0 && counter->shouldDeleteCounter()) {
                delete counter;
            }
        }
        counter = nullptr;
        pointer = nullptr;
    }
};

#endif //L5_BORROWINGPOINTER_H