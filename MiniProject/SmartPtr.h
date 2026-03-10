//
// Created by Kuba Iwanicki on 19/01/2026.
//

#ifndef LAB6_SMARTPTR_H
#define LAB6_SMARTPTR_H

template <typename T>
class SmartPtr {
    private:
    T* ptr;
    int* refCount;

    void release() {
        if (refCount) {
            (*refCount)--;
            if ((*refCount) == 0) {
                delete ptr;
                delete refCount;
                ptr = nullptr;
                refCount = nullptr;
            }
        }
    }

    public:
    explicit SmartPtr(T* p = nullptr) : ptr(p), refCount(nullptr) {
        if (p) {
            refCount = new int(1);
        }
    }

    SmartPtr(const SmartPtr& other) : ptr(other.ptr), refCount(other.refCount) {
        if (refCount) {
            (*refCount)++;
        }
    }

    SmartPtr& operator=(const SmartPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            if (refCount) {
                (*refCount)++;
            }
        }
        return *this;
    }

    ~SmartPtr() {
        release();
    }

    SmartPtr(SmartPtr&& other) noexcept : ptr(other.ptr), refCount(other.refCount) {
        other.ptr = nullptr;
        other.refCount = nullptr;
    }

    SmartPtr& operator=(SmartPtr&& other) noexcept {
        if (this != &other) {
            release();

            ptr = other.ptr;
            refCount = other.refCount;

            other.ptr = nullptr;
            other.refCount = nullptr;
        }
        return *this;
    }

    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }
    bool isNull() const { return ptr == nullptr; }
};

#endif //LAB6_SMARTPTR_H