//
// Created by Kuba Iwanicki on 27/10/2025.
//

#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <iostream>


#define DEFAULT_LENGTH 10

class Number {
private:
    int* digits;
    int length;
    bool isNegative;

    void resize(int newLength);
    void trim();
    int compareMagnitude(const Number &other) const;

public:
    Number(); // domyślny
    ~Number(); // destruktor
    Number& operator=(int value);

    // zad 4
    Number(const Number& other); // kopiujący
    Number& operator=(const Number& other); // poprawiony operator przypisania

    // zad 5
    std::string toString() const;

    // zad 6
    Number operator+(const Number& other) const;

    Number operator+(int value) const;

    static Number addMagnitude(const Number &a, const Number &b);
    static Number subMagnitude(const Number &a, const Number &b);

    Number &operator--();

    Number operator--(int);

    Number operator-(const Number& other) const;

    Number operator-(int value) const;

    Number operator*(const Number& other) const;

    Number operator*(int value) const;

    Number operator/(const Number& other) const;

    Number operator/(int value) const;

    friend std::ostream& operator<<(std::ostream& os, const Number& num);
};

#endif // NUMBER_H