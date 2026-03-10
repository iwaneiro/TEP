//
// Created by Kuba Iwanicki on 27/10/2025.
//

#include "Number.h"
#include <sstream>

// zad1
Number::Number() {
    length = DEFAULT_LENGTH;
    digits = new int[length];
    for (int i=0;i<length;++i) {
        digits[i] = 0;
    }
    length = 1;
    isNegative = false;
}

Number::~Number() {
    delete[] digits;
}

Number& Number::operator=(const int value) {
    int tempVal = value;
    if (value<0) {
        isNegative = true;
        tempVal = -value;
    } else {
        isNegative = false;
    }
    if (tempVal==0) {
        resize(1);
        digits[0] = 0;
        return *this;
    }

    int tempLength = 0;
    int valCopy = tempVal;
    while (valCopy>0) {
        valCopy/=10;
        tempLength++;
    }
    resize(tempLength);

    // wypełnienie tablicy (najmniej znaczaca cyfra na indeksie 0)
    int i = 0;
    while (tempVal > 0) {
        digits[i] = tempVal % 10;
        tempVal /= 10;
        i++;
    }

    return *this;
}

// Zad 2 (c_num_0 = c_num_1 powoduje: Wyciek pamięci(utrata wskaźnika na dane c_num0) oraz błąd double free (podwojne zwolnienie) przy wyjsciu z programu

// void Number::operator=(const Number &other) {
//     digits = other.digits;
//     length = other.length;
// }


// Zad 3- usuniecie destruktora spowoduje brak bledu double free, ale za to bedą wycieki pamięci (bo pamiec new[] nie bylaby zwalniana)


// zad 4
Number::Number(const Number &other) {
    // alokacja nowej pamieci
    length = other.length;
    isNegative= other.isNegative;
    digits = new int[length];

    // deep copy
    for (int i=0; i<length;++i) {
        digits[i] = other.digits[i];
    }
}

Number& Number::operator=(const Number &other) {
    // Sprawdzenie autoprzypisania
    if (this==&other) {
        return *this;
    }
    // zwoleninei starej pamieci
    delete[] digits;

    // alokacja nowej pamieci
    length=other.length;
    isNegative=other.isNegative;
    digits=new int[length];

    // deep copy
    for (int i = 0;i<length;++i) {
        digits[i] = other.digits[i];
    }

    return *this;
}

// Zad 5
std::string Number::toString() const {
    if (length==1 && digits[0]==0) {
        return "0";
    }
    std::stringstream ss;
    if (isNegative) {
        ss << "-";
    }

    for (int i=length-1; i>=0;--i) {
        ss<<digits[i];
    }
    return ss.str();
}

// Zad 6
Number Number::operator+(const Number &other) const {
    // te same znaki
    if (isNegative == other.isNegative) {
        Number result = addMagnitude(*this, other);
        result.isNegative = isNegative;
        return result;
    }

    // różne znaki
    int magCmp = compareMagnitude(other);
    if (magCmp==0) {
        return Number(); // zwroc 0
    }
    if (magCmp>0) {
        Number result = subMagnitude(*this, other);
        result.isNegative = isNegative; // Znak wiekszej liczby
        return result;
    } else {
        Number result = subMagnitude(other,*this);
        result.isNegative = other.isNegative; // Znak wiekszej liczby
        return result;
    }
}

Number Number::operator+(int value) const {
    Number other;
    other = value;
    return *this+other;
}


Number Number::operator-(const Number &other) const {
    // A - B jako A + (-B)
    Number temp = other;    // konstruktor kopiujacy
    temp.isNegative = !temp.isNegative;    // odwrocenie znaku

    return *this + temp;
}

Number Number::operator-(int value) const {
    Number other;
    other = value;

    return *this - other;
}



Number Number::operator*(const Number& other) const {
    // mnożenie przez 0
    if ((length == 1 && digits[0] == 0) || (other.length == 1 && other.digits[0] == 0)) {
        return Number();
    }

    Number result;
    result.resize(length + other.length); // wynik ma max tyle cyfr

    // mnozenie pisemne
    for (int i = 0; i < length; ++i) {
        int carry = 0;
        for (int j = 0; j < other.length; ++j) {
            int product = digits[i] * other.digits[j] + result.digits[i + j] + carry;
            result.digits[i + j] = product % 10;
            carry = product / 10;
        }
        result.digits[i + other.length] += carry;
    }

    result.trim();

    // znak +/-
    result.isNegative = (isNegative != other.isNegative);

    return result;
}

Number Number::operator*(int value) const {
    Number other;
    other = value;

    return *this*other;
}

 Number Number::operator/(const Number &other) const {
     // dzielenie przez  0
    if (other.length==1 && other.digits[0]==0) {
        exit(EXIT_FAILURE);
    }
    // 0 / X
    if (length==1 && digits[0]==0) {
        return Number();
    }

    //  A < B -> A/B=0 (bo dzielenie calkowite)
    if (compareMagnitude(other)<0) {
        return Number();
    }

    // dzielenie pisemne
    std::string answer; // budujemy wynik jako String
    Number remainder;
    remainder = 0;
    Number divisor = other;
    divisor.isNegative = false;

    // iterujemy po cyfrach this od najbardziej znaczacej
    for (int i= length-1; i>=0;--i) {
        // przesuniecie reszty o jeden w lewo (czyli *10)
        if (!(remainder.length==1 && remainder.digits[0]==0)) {
            int* newDigits = new int[remainder.length+1];
            newDigits[0] = 0;
            for (int j =0; j<remainder.length; ++j) {
                newDigits[j+1] = remainder.digits[j]; // przesuniecie starych cyfr
            }
            delete[] remainder.digits;
            remainder.digits = newDigits;
            remainder.length++;
        }
        // dodanie aktualnej cyfry do reszty
        Number currentDigit;
        currentDigit = digits[i];
        remainder = remainder + currentDigit;

        // obliczanie cyfry ilorazu (ile razy divider miesci sie w remainderze)
        int qDigit = 0;
        while (remainder.compareMagnitude(divisor)>=0) {
            remainder = remainder - divisor;
            qDigit++;
        }
        // dopisanie liczby do wyniku String
        if (!answer.empty() || qDigit > 0) {
            answer += (char)('0' + qDigit); // konwertowanie int na char
        }
    }

    if (answer.empty()) {
        answer = "0";
    }

    // konwertowanie stringa na Number
    Number result;
    result.resize(answer.length());
    for (int i = 0; i < (int)answer.length(); ++i) {
        result.digits[i] = answer[answer.length() - 1 - i] - '0';
    }

    result.trim();

    // znak tak samo jak przy mnozeniu
    if (result.length == 1 && result.digits[0] == 0) {
        result.isNegative = false;
    } else {
        result.isNegative = (isNegative != other.isNegative);
    }

    return result;
}

Number Number::operator/(int value) const {
    Number other;
    other = value;

    return *this/other;
}


// pomocnicze
void Number::resize(int newLength) {
    if (newLength<=0) newLength=1;

    int* newDigits = new int[newLength];
    int minLength = (newLength < length) ? newLength : length;

    //kopia starych danych
    for (int i = 0; i < minLength; ++i) {
        newDigits[i] = digits[i];
    }

    // wypelnienie reszty zerami
    for (int i = minLength; i < newLength; ++i) {
        newDigits[i] = 0;
    }

    delete[] digits;
    digits = newDigits;
    length = newLength;
}

// usuwa wiodące zera
void Number::trim() {
    int i = length - 1;
    while (i > 0 && digits[i] == 0) {
        i--;
    }
    resize(i + 1);

    if (length == 1 && digits[0] == 0) {
        isNegative = false;
    }
}

int Number::compareMagnitude(const Number &other) const {
    if (length>other.length) return 1;
    if (length<other.length) return -1;

    for (int i=length-1; i>=0; --i) {
        if (digits[i]>other.digits[i]) return 1;
        if (digits[i]<other.digits[i]) return -1;
    }
    return 0;
}

Number Number::addMagnitude(const Number& a, const Number& b) {
    int max_len = std::max(a.length, b.length);
    Number result;
    result.resize(max_len + 1); // +1 dla ewentualnego przeniesienia

    int carry = 0;
    for (int i = 0; i < max_len; ++i) {
        int d1 = (i < a.length) ? a.digits[i] : 0;
        int d2 = (i < b.length) ? b.digits[i] : 0;
        int sum = d1 + d2 + carry;
        result.digits[i] = sum % 10;
        carry = sum / 10;
    }
    result.digits[max_len] = carry;
    result.trim();
    return result;
}


// zakładamy |a| >= |b|
Number Number::subMagnitude(const Number& a, const Number& b) {
    Number result;
    result.resize(a.length);

    int borrow = 0;
    for (int i = 0; i < a.length; ++i) {
        int d1 = a.digits[i];
        int d2 = (i < b.length) ? b.digits[i] : 0;

        int diff = d1 - d2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits[i] = diff;
    }
    result.trim();
    return result;
}


std::ostream& operator<<(std::ostream& os, const Number& num) {
    os << num.toString();
    return os;
}

Number& Number::operator--() {
    Number one;
    one = 1;

    *this = *this - one;
    return *this;
}

Number Number::operator--(int) {
    Number oldVal = *this;

    --(*this);
    return oldVal;
}