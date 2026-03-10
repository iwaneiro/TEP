//
// Created by Kuba Iwanicki on 14/10/2025.
//

#include <__config>

bool b_alloc_table2_dim(int ***piTable, int iSizeX, int iSizeY) {   // ***piTable by móc modyfikoeać wartość int **
    if (iSizeX < 1 || iSizeY < 1) {
        return false;
    }
    // alokujemy tablice wskaźników
    *piTable = new int*[iSizeX];

    // alokujemy kazdy wiersz
    for (int i = 0; i < iSizeX; i++) {
        (*piTable)[i] = new int[iSizeY];
    }
    return true;
}

bool b_dealloc_table2_dim(int ***piTable, int iSizeX, int iSizeY) {     // iSizeY niepotrzebne
    if (piTable == nullptr || *piTable == nullptr|| iSizeX<1) {
        return false;
    }

    // dealokujemy wiersze
    for (int i = 0; i < iSizeX; i++) {
        if ((*piTable)[i] != nullptr) {
            delete[] (*piTable)[i];
        }
    }

    // dealokujemy tablicę wskaźników
    delete[] *piTable;
    *piTable = nullptr;

    return true;
}