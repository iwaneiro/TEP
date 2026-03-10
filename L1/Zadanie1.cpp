//
// Created by Kuba Iwanicki on 12/10/2025.
//

#include "Zadanie1.h"
#include "Constants.h"
#include <iostream>

void v_alloc_table_fill_34(int iSize) {
    if (iSize < 1) {
        std::cout << "Rozmiar tablicy musi byc wiekszy niz 0" << std::endl;
        return;
    }
//  dynamiczna alokacja tablicy
    int *pi_table;
    pi_table = new int[iSize];

// wypełnienie 34
    for (int i = 0; i < iSize; i++) {
        pi_table[i] = FILL_VALUE;
    }
// print stanu tablicy
    for (int i = 0; i < iSize; i++) {
        std::cout << pi_table[i] << " ";
    }

// dealokacja  tablicy
    delete[] pi_table;
}
