//
// Created by Kuba Iwanicki on 14/10/2025.
//

#ifndef CTABLE_H
#define CTABLE_H

#include <string>

class CTable {
public:
    CTable(); // konstruktor bezparametrowy
    CTable(const std::string& sName, int iTableLen); // parametrametrowy
    CTable(const CTable &pcOther); // kopiujący
    ~CTable(); // destruktor

    void vSetName(const std::string& sName);
    bool bSetNewSize(int iTableLen);
    CTable *pcClone() const;

    void insertHere(const CTable &pcOther, int i_index);

    bool bSetValue(int i_index, int i_value) const;

    void vPrint() const;

private:
    std::string s_name;
    int *pi_table;
    int i_table_len;

    void v_print_message(const std::string &sMessage) const;
};

void v_mod_tab_ptr(CTable *pcTab, int iNewSize);
void v_mod_tab_val(CTable cTab, int iNewSize);

#endif // CTABLE_H