//
// Created by Kuba Iwanicki on 14/01/2026.
//

#ifndef L5_SMARTPOINTER_H
#define L5_SMARTPOINTER_H
#include "ReferenceCounter.h"
#include "BorrowingPointer.h"
template <typename T> class BorrowingPointer;


template <typename T>
class SmartPointer {
    friend class BorrowingPointer<T>;
public:
    // Konstr
    SmartPointer(T* ptr) {
        pointer = ptr;
        counter = new ReferenceCounter();
        counter->add();
    }
    // Kopiujacy
    SmartPointer(const SmartPointer& other) {
        pointer = other.pointer;
        counter = other.counter;
        counter->add();
    }
    // Destr
    ~SmartPointer() {
        release();
    }

    // Przypisania
    SmartPointer& operator=(const SmartPointer& other) {
        if (this != &other) {
            release();
            pointer = other.pointer;
            counter = other.counter;
            counter->add();
        }
        return *this;
    }
    // Dostepu
    T& operator*()  {return *pointer;}
    const T& operator*() const { return *pointer; }
    T* operator->()  {return pointer;}
    const T* operator->() const { return pointer; }

    int getRefCount() const { return counter->get(); }

    SmartPointer(SmartPointer&& other) noexcept {
        pointer = other.pointer;
        counter = other.counter;

        other.pointer = nullptr;
        other.counter = nullptr;
    }

    SmartPointer& operator=(SmartPointer&& other) noexcept {
        if (this != &other) {
            release();

            pointer = other.pointer;
            counter = other.counter;

            other.pointer = nullptr;
            other.counter = nullptr;
        }
        return *this;
    }

    BorrowingPointer<T> borrow() {
        return BorrowingPointer<T>(*this);
    }

private:
    T* pointer;
    ReferenceCounter* counter;
    void release() {
        if (!counter) return;

        if (counter->dec() == 0) {
            counter -> invalidateListeners();
            delete pointer;
        }
        if (counter -> shouldDeleteCounter()) {
            delete counter;
        }
        counter = nullptr;
        pointer = nullptr;
    }
};
#endif //L5_SMARTPOINTER_H