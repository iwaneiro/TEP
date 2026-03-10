//
// Created by Kuba Iwanicki on 14/01/2026.
//

#ifndef L5_REFERENCECOUNTER_H
#define L5_REFERENCECOUNTER_H
#include <vector>

class ReferenceCounter {
public:
    ReferenceCounter() : count(0), borrowCount(0) {}
    int add() {return ++count;}
    int dec() {return --count;}
    int get() const {return count;}

    int borrowAdd() {return ++borrowCount;}
    int borrowDec() {return --borrowCount;}
    int borrowGet() const {return borrowCount;}

    bool shouldDeleteCounter() const {
        return count == 0 && borrowCount == 0;
    }

    void addListener(void* ptrAddress) {
        listeners.push_back(ptrAddress);
    }

    void removeListener(void* ptrAddress) {
        for (auto it = listeners.begin(); it != listeners.end(); ++it) {
            if (*it == ptrAddress) {
                listeners.erase(it);
                return;
            }
        }
    }

    void invalidateListeners() {
        for (void* ptrAddress : listeners) {
            *(static_cast<void**>(ptrAddress)) = nullptr;
        }
        listeners.clear();
    }


private:
    int count;
    int borrowCount;
    std::vector<void*> listeners;
};


#endif //L5_REFERENCECOUNTER_H