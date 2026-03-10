#include <iostream>
#include "Tree.h"
#include "Result.h"
#include "Error.h"
#include "FileSaver.h"

void printHeader(const std::string& title) {
    std::cout << "\n========================================\n";
    std::cout << "TEST: " << title << "\n";
}

int main() {
    // ZAD 1
    printHeader("Zadanie 1: Klasa Error");
    Error* e1 = new Error("Testowy blad");
    std::cout << "Komunikat bledu: " << e1->getMessage() << std::endl;
    delete e1;



    // ZAD 2
    printHeader("Zadanie 2: Result<int, Error>");
    // Test ok
    Result<int, Error> intOk = Result<int, Error>::ok(123);

    if (intOk.isSuccess()) {
        std::cout << "Udalo sie utworzyc Result z wartoscia: " << intOk.getValue() << std::endl;
    } else {
        std::cout << "Result powinien byc sukcesem." << std::endl;
    }

    // Pojedynczy błąd
    Result<int, Error> intFail = Result<int, Error>::fail(new Error("Nieudane obliczenia"));
    if (!intFail.isSuccess()) {
        std::cout << "Result zawiera blad: " << intFail.getErrors()[0]->getMessage() << std::endl;
    }

    Result<int, Error> copy = intFail;
    Error* err1 = intFail.getErrors()[0];
    Error* err2 = copy.getErrors()[0];
    std::cout << "Adres bledu 1: " << err1 << std::endl;
    std::cout << "Adres bledu 2: " << err2 << std::endl;

    // Wektor błędów
    std::vector<Error*> errors;
    errors.push_back(new Error("Blad A"));
    errors.push_back(new Error("Blad B"));
    Result<int, Error> intMultiFail = Result<int, Error>::fail(errors);

    if (!intMultiFail.isSuccess()) {
        std::cout << "Result zawiera " << intMultiFail.getErrors().size() << " bledy." << std::endl;
    }



    // ZAD 3
    printHeader("Zadanie 3: Result<void, Error>");

    Result<void, Error> voidOk = Result<void, Error>::ok();
    if (voidOk.isSuccess()) {
        std::cout << "Operacja void zakonczona sukcesem." << std::endl;
    }

    Result<void, Error> voidFail = Result<void, Error>::fail(new Error("Awaria void"));
    if (!voidFail.isSuccess()) {
        std::cout << "Operacja void zakonczona bledem: "
                  << voidFail.getErrors()[0]->getMessage() << std::endl;
    }



    // ZAD 4
    printHeader("Zadanie 4: Tworzenie Drzewa (Result<Tree*, Error>)");

    // Poprawna formuła
    std::string validFormula = "+ * 5 3 2";
    std::cout << "Proba utworzenia drzewa z: '" << validFormula << "'" << std::endl;

    Result<Tree*, Error> treeOk = Tree::createTree(validFormula);

    if (treeOk.isSuccess()) {
        Tree* myTree = treeOk.getValue();
        std::cout << "Drzewo utworzone. Wynik obliczen dla pustych zmiennych: ";
        std::vector<double> vals;
        std::cout << myTree->calculate(vals) << std::endl;
        std::cout << "Struktura (prefix): ";
        myTree->print();
    } else {
        std::cout << "Nie udalo sie utworzyc poprawnego drzewa." << std::endl;
    }

    // Niepoprawna formuła (za mało argumentów)
    std::string invalidFormula = "+ 5";
    std::cout << "\nProba utworzenia drzewa z: '" << invalidFormula << "'" << std::endl;

    Result<Tree*, Error> treeFail = Tree::createTree(invalidFormula);

    if (!treeFail.isSuccess()) {
        std::cout << "Prawidlowo wykryto bledy (" << treeFail.getErrors().size() << "):" << std::endl;
        std::vector<Error*> errs = treeFail.getErrors();
        for (size_t i = 0; i < errs.size(); ++i) {
            std::cout << " - " << errs[i]->getMessage() << std::endl;
        }
    } else {
        std::cout << "Utworzono drzewo mimo blednej formuly!" << std::endl;
    }



    // ZAD 5
    printHeader("Zadanie 5: Zapis do pliku (FileSaver)");

    FileSaver saver;

    std::string fileTreeOk = "test_tree_ok.txt";
    saver.save(fileTreeOk, treeOk);
    std::cout << "Zapisano poprawne drzewo do: " << fileTreeOk << std::endl;

    std::string fileTreeErr = "test_tree_err.txt";
    saver.save(fileTreeErr, treeFail);
    std::cout << "Zapisano bledy drzewa do: " << fileTreeErr << std::endl;

    std::string fileIntErr = "test_int_err.txt";
    saver.save(fileIntErr, intFail);
    std::cout << "Zapisano bledy int do: " << fileIntErr << std::endl;



    if (treeOk.isSuccess()) {
        delete treeOk.getValue();
    }


    // MOD
    // Result<int, int> crash = Result<int, int>::ok(5);

    return 0;
}