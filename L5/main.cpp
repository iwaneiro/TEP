#include <iostream>
#include <stdexcept>
#include "SmartPointer.h"
#include "BorrowingPointer.h"
#include "Tree.h"


int main()
{

    Tree tree1, tree2, tree3, tree4, result;

    tree1.enter("+ + a a a");
    tree2.enter("+ + b b b");
    tree3.enter("+ + c c c");
    tree4.enter("+ + d d d");

    std::cout << "--- TEST 1: Przypisanie (Kopiowanie) ---\n";
    std::cout << "----------------------------------------\n";

    tree4 = tree3;

    std::cout << "Tree4: ";
    tree4.print();
    std::cout << "\nTree3: ";
    tree3.print();
    std::cout << "\n\n";


    std::cout << "--- TEST 2: std::move (Przenoszenie) ---\n";
    std::cout << "----------------------------------------\n";

    tree4 = std::move(tree3);

    std::cout << "Tree4: ";
    tree4.print();
    std::cout << "\nTree3 (powinno byc puste): '";
    tree3.print();
    std::cout << "'\n\n";


    std::cout << "=== TEST 3: Normalne dodawanie z Move Semantics ===\n";
    std::cout << "---------------------------------------------------\n";

    result = tree1 + tree2;

    std::cout << "Wynik: ";
    result.print();
    std::cout << "\n\n";


    std::cout << "=== TEST 4: Proba dodania bez Move Semantics ===\n";
    std::cout << "----------------------------------\n";

    result = static_cast<const Tree&>(tree1 + tree2);

    std::cout << "Wynik: ";
    result.print();
    std::cout << "\n\n";


    std::cout << "=== MODYFIKACJA ===\n";
    std::cout << "---------------------------------------------------\n";

    SmartPointer<int> spInt(new int(999));
    std::cout << "Wartosc pod spInt: " << *spInt << "\n";
    std::cout << "Licznik referencji: " << spInt.getRefCount() << "\n";

    {
        std::cout << "-- Tworzenie BorrowingPointer (wewnatrz zakresu) --\n";
        BorrowingPointer<int> borrowPtr = spInt.borrow();

        std::cout << "Wartosc przez borrowPtr: " << *borrowPtr << "\n";
        std::cout << "Licznik po pozyczeniu: " << spInt.getRefCount() << "\n";
    }

    std::cout << "\n=== TEST 6: Automatyczne zerowanie (Invalidate) ===\n";
    std::cout << "---------------------------------------------------\n";

    BorrowingPointer<int> weakInt;

    {
        std::cout << "-- Wejscie w zakres tymczasowy --\n";
        SmartPointer<int> tempSp(new int(100));
        weakInt = tempSp.borrow();

        std::cout << "Wewnatrz: *weakInt = " << *weakInt << "\n";
        std::cout << "-- Wyjscie z zakresu --\n";
    }

    std::cout << "Poza zakresem weakInt:\n";

    if (weakInt.get() == nullptr) {
        std::cout << "Wskaznik jest nullptr\n";
    } else {
        std::cout << "BLAD!\n";
    }

    std::cout << "Proba dereferencji:\n";
    try {
        int val = *weakInt;
        std::cout << "BLAD! Odczytano wartosc " << val << "\n";
    } catch (const std::runtime_error& e) {
        std::cout << "SUKCES! Zlapano wyjatek: " << e.what() << "\n";
    }

    return 0;
}

// ODP NA PYTANIA
// Czy mozna przechowywac wskaznik bardziej ogolny (np. void*)?
// Mozna uzyc void*, ale to niebezpieczne.
// Zalety: Wskaznik jest uniwersalny, moze wskazywac na dowolny typ.
// Wady: 'delete' na void* nie wywola destruktora obiektu, wiec jesli obiekt
// mial w srodku dynamiczna pamiec (jak Node w Tree), to bedzie wyciek.
// Nie dzialaja tez operatory -> i *.

// Co sie stanie, gdy inteligentny wskaznik dostanie adres pamieci statycznej?
// Program sie wysypie (crash / undefined behavior).
// Wyjasnienie: Inteligentny wskaznik w destruktorze robi 'delete'.
// Instrukcji 'delete' mozna uzywac tylko na pamieci ze sterty (new), a nie ze stosu.
