//
// Created by Kuba Iwanicki on 14/10/2025.
//

#include "CTable.h"
#include "Constants.h"
#include <iostream>

void CTable::v_print_message(const std::string &sMessage) const {
    std::cout<<sMessage<<s_name<<END_QUOTE<< std::endl;
}

// domyślny konstruktor
CTable::CTable() {
    s_name = DEFAULT_NAME;
    i_table_len = DEFAULT_TABLE_SIZE;
    pi_table = new int[i_table_len];
    v_print_message(MSG_BEZPARAM);
}

// paramteryczny
CTable::CTable(const std::string& sName, int iTableLen) {
    s_name = sName;
    i_table_len = iTableLen;

    // jeśli rozmiar jest niepoprawny - użyj domyślnego
    if (i_table_len<=0) {
        i_table_len = DEFAULT_TABLE_SIZE;
    }
    pi_table = new int[i_table_len];
    v_print_message(MSG_PARAM);
}

// kopiujący
CTable::CTable(const CTable &pcOther) {
    s_name = pcOther.s_name+CLONE_SUFFIX;
    i_table_len = pcOther.i_table_len;

    // alokujemy nowy obszar pamięci, ktory bedzie kopią
    pi_table = new int[i_table_len];
    //kopiowanie elementów
    for (int i=0; i<i_table_len; i++) {
        pi_table[i] = pcOther.pi_table[i];
    }
    v_print_message(MSG_COPY);
}

// destruktor
CTable::~CTable() {
    // jawne zwolnienie pamięci
    v_print_message(MSG_DELETE);
    delete[] pi_table;
}

void CTable::vSetName(const std::string& sName) {
    s_name = sName;
}

// zmiana rozmiaru tablicy (pozbywamy sie starej, aktualizujemy rozmiar i tworzymy nową)
bool CTable::bSetNewSize(int iTableLen) {
    if (i_table_len <= 0) {
        return false;
    }
    // alokacja nowej tablicy o nowym rozmiarze
    int *pi_new_table = new int[iTableLen];

    // kopiowanie dotychczasowych elementów (min ze starej lub nowej)
    int i_copy_len;
    if (iTableLen < i_table_len) i_copy_len = iTableLen;
    else i_copy_len = i_table_len;
    for (int i = 0; i < i_copy_len; i++)
    {
        pi_new_table[i] = pi_table[i];
    }

    // zwolnienie starej tablicy (dealokacja)
    delete[] pi_table;

    // przypisanie wskaźników i rozmiaru
    pi_table = pi_new_table;
    i_table_len = iTableLen;
    return true;
}

CTable *CTable::pcClone() const {
    // uzywamy konstrukotra kopiującego
    return new CTable(*this);
}

void CTable::insertHere(const CTable &pcOther, int i_index) {
    if (i_index < 0 || i_index > i_table_len) {
        return;
    }

    if (pcOther.i_table_len <= 0) {
        return;
    }

    int i_new_size = i_table_len + pcOther.i_table_len;
    int *pi_new_table = new int[i_new_size];

    for (int i = 0; i < i_index; i++) {
        pi_new_table[i] = pi_table[i];
    }

    for (int i = 0; i < pcOther.i_table_len; i++) {
        pi_new_table[i_index + i] = pcOther.pi_table[i];
    }

    for (int i = i_index; i < i_table_len; i++) {
        pi_new_table[i + pcOther.i_table_len] = pi_table[i];
    }

    delete[] pi_table;
    pi_table = pi_new_table;
    i_table_len = i_new_size;
}

bool CTable::bSetValue(int i_index, int i_value) const {
    if (i_index < 0 || i_index >= i_table_len) {
        return false;
    }
    pi_table[i_index] = i_value;
    return true;
}

void CTable::vPrint() const {
    std::cout << "Stan obiektu '" << s_name  << "': [ ";
    for (int i = 0; i < i_table_len; i++) {
        std::cout << pi_table[i] << " ";
    }
    std::cout << "]" << std::endl;
}