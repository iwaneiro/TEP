//
// Created by Kuba Iwanicki on 14/10/2025.
//

#include <iostream>
#include "Zadanie1.h"
#include "Zadanie2_3.h"
#include "CTable.h"
#include "Constants.h"

// przekazywanie przez wskaźnik - trwałe zmiany na oryginalnym obiekcie
void v_mod_tab_ptr(CTable *pcTab, int iNewSize) {
    if (pcTab != nullptr) {
        pcTab->vSetName(MOD_PTR_NAME);
        pcTab->bSetNewSize(iNewSize);
    }
}

// przekazywanie przez wartość - zmiany na kopii
void v_mod_tab_val(CTable cTab, int iNewSize) {
    cTab.bSetNewSize(iNewSize);
}


int main() {
    // zadanie 1
    std::cout << "\nZADANIE 1" << std::endl;
    std::cout << "Test z poprawnym rozmiarem (5):" << std::endl;
    v_alloc_table_fill_34(5);
    std::cout << "\n\nTest z niepoprawnym rozmiarem:" << std::endl;
    v_alloc_table_fill_34(-5);

    // zadania 2 i 3
    std::cout << "\nZADANIA 2 i 3" << std::endl;
    int **pi_table_2d;
    int size_x = 5;
    int size_y = 3;

    // test alokacji
    if (b_alloc_table2_dim(&pi_table_2d, size_x, size_y)) {
        std::cout << "Tablica 2D o wymiarach " << size_x << "x" << size_y << " zostala poprawnie zaalokowana.\n" << std::endl;
        // wypełnienie przykładowymi danymi i wyświetlenie
        for (int i = 0; i < size_x; i++) {
            for (int j = 0; j < size_y; j++) {
                pi_table_2d[i][j] = i * 10 + j;
                std::cout << pi_table_2d[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << "Blad podczas alokacji tablicy 2D." << std::endl;
    }

    // test dealokacji
    if (b_dealloc_table2_dim(&pi_table_2d, size_x, size_y)) {
        std::cout << "\nTablica 2D zostala poprawnie zdealokowana." << std::endl;
    } else {
        std::cout << "\nBlad podczas dealokacji tablicy 2D." << std::endl;
    }


    // zadanie 4 - CTable
    std::cout << "\nZADANIE 4" << std::endl;

    std::cout << "Test konstruktorow i destruktorow (alokacja statyczna i dynamiczna)" << std::endl;
    std::cout << "      Tworzenie obiektu statycznego (bezparametrowy):" << std::endl;
    CTable c_static_obj;

    std::cout << "\n    Tworzenie obiektu dynamicznego (parametryczny):" << std::endl;
    CTable *pc_dynamic_obj = new CTable("dynamic_obj", 7);

    pc_dynamic_obj->insertHere(c_static_obj,2);

    std::cout << "\n    Tworzenie obiektu przez konstruktor kopiujacy:" << std::endl;
    CTable c_copied_obj(*pc_dynamic_obj);

    std::cout << "\n    Usuwanie obiektu dynamicznego:" << std::endl;
    delete pc_dynamic_obj;

    std::cout << "\nTest pcClone() " << std::endl;
    CTable c_source_obj("source", 3);
    CTable *pc_cloned_obj = c_source_obj.pcClone();
    std::cout << "\nUsuwanie sklonowanego obiektu:" << std::endl;
    delete pc_cloned_obj;

    std::cout << "\nModyfikacja obiektu (przez wskaznik vs przez wartosc)" << std::endl;
    CTable c_mod_test("original", 10);

    // modyfikacja przez wskaźnik - zmienia oryginalny obiekt
    std::cout << "\nModyfikacja przez wskaźnik:" << std::endl;
    v_mod_tab_ptr(&c_mod_test, 20);

    // modyfikacja przez wartość - tworzy kopię i na niej operuje
    std::cout << "\nModyfikacja przez wartość:" << std::endl;
    v_mod_tab_val(c_mod_test, 30);

    std::cout << "\nTest tablicy obiektow CTable" << std::endl;
    std::cout << "Tworzenie tablicy 3 obiektow (alokacja statyczna):" << std::endl;
    CTable c_table_array[3];
    std::cout << "\nTablica obiektow zostanie zniszczona automatycznie na koncu programu." << std::endl;



    // modyfikacja
    CTable c_dest("destination", 5);
    for (int i = 0; i < 5; i++) {
        c_dest.bSetValue(i, (i + 1) * 10);
    }

    CTable c_src("source", 3);
    c_src.bSetValue(0, 99);
    c_src.bSetValue(1, 98);
    c_src.bSetValue(2, 97);

    std::cout << "Stan poczatkowy:" << std::endl;
    c_dest.vPrint();
    c_src.vPrint();

    std::cout << "\nWstawienie na indeksie 2" << std::endl;
    c_dest.insertHere(c_src, 2);
    c_dest.vPrint();

    std::cout << "\nWstawienie na poczatku (indeks 0)" << std::endl;
    c_dest.insertHere(c_src, 0);
    c_dest.vPrint();

    std::cout << "\nWstawienie na koncu (indeks 11)" << std::endl;
    c_dest.insertHere(c_src, 11);
    c_dest.vPrint();

    std::cout << "\nWstawienie poza" << std::endl;
    c_dest.insertHere(c_src, 1000);
    c_dest.vPrint();

    std::cout << "\nKoniec programu.\n";
    return 0;
}