//
// Created by Kuba Iwanicki on 27/10/2025.
//

#include "number.h"
#include <iostream>

int main() {
    Number num0, num1;

    num0 = 333;
    num1 = 535;

    std::cout << "Przed przypisaniem (num0 = num1):" << std::endl;
    std::cout << "num0: " << num0 << std::endl;
    std::cout << "num1: " << num1 << std::endl;

    num0 = num1;

    std::cout << "Po przypisaniu (num0 = num1):" << std::endl;
    std::cout << "num0: " << num0 << std::endl;
    std::cout << "num1: " << num1 << std::endl;

    Number num2 = num0; // użycie konstruktora kopiującego
    num2 = 99;
    std::cout << "Konstruktor kopiujacy:" << std::endl;
    std::cout << "num0: " << num0 << std::endl;
    std::cout << "num2 (po num2 = 99): " << num2 << std::endl;


    Number test_str;
    test_str = -12345;
    std::cout << "Wartosc obiektu jako string: " << test_str.toString() << std::endl; //


    std::cout << "\n---Dodawanie---" << std::endl;
    Number a, b, c, d;
    a = 1000;
    b = 999;
    std::cout << (a + b) << std::endl;
    a = -50;
    b = 150;
    std::cout << (a + b) << std::endl;
    a = 50;
    b = -150;
    std::cout << (a + b) << std::endl; //
    a = -50;
    b = -150;
    std::cout << (a + b) << std::endl;

    std::cout << "---Odejmowanie---" << std::endl;
    a = 1000;
    b = 999;
    std::cout << (a - b) << std::endl;
    a = 10;
    b = 500;
    std::cout << (a - b) << std::endl; //
    a = -100;
    b = 50;
    std::cout << (a - b) << std::endl;
    a = -100;
    b = -150;
    std::cout << (a - b) << std::endl;

    std::cout << "---Mnozenie---" << std::endl;
    a = 123;
    b = 5;
    std::cout << (a * b) << std::endl;
    a = 123456;
    b = -100;
    std::cout << (a * b) << std::endl; //
    a = 99;
    b = 0;
    std::cout << (a * b) << std::endl;


    std::cout << "--- Dzielenie---" << std::endl;
    a = 100;
    b = 100;
    std::cout << (a / b) << std::endl;
    a = 101;
    b = 10;
    std::cout << (a / b) << std::endl; //
    a = 123;
    b = -3;
    std::cout << (a / b) << std::endl; //
    a = 99;
    b = 100;
    std::cout << (a / b) << std::endl;
    // a = 100;
    // b = 0;
    // std::cout << (a / b) << std::endl; //


    a = 123456789;
    b = 987654321;
    c = a * b;
    std::cout << "\nDuze liczby (" << a << " * " << b << "):" << std::endl;
    std::cout << c << std::endl;

    d = c / a;
    std::cout << "(" << c << " / " << a << ") = " << d << std::endl;


    a = 100;
    std::cout << a+15<<std::endl;
    std::cout << a-15<<std::endl;
    std::cout << a*15<<std::endl;
    std::cout << a/15<<std::endl;


    Number result;
    result = 5;
    std::cout << "\n"<< result-- << std::endl;
    std::cout << result << std::endl;

    result = 5;
    std::cout <<"\n"<< --result << std::endl;
    std::cout << result << std::endl;

    return 0;


}