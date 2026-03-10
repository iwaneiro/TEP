//
// Created by Kuba Iwanicki on 19/01/2026.
//

#ifndef LAB6_PROBLEM_H
#define LAB6_PROBLEM_H
#include <vector>

// Miasto
struct Node {
    int id;
    double x, y;
};

class Evaluator;

class Problem {
    friend class Evaluator;

private:
    std::vector<Node> nodes;
    std::vector<int> demands;
    std::vector<double> distances;
    std::vector<int> permutation; // Sekwencja klientow

    int capacity;   // Pojemnosc ciezarowki
    int numberOfGroups; // Ilosc dostepnych ciezaorwek
    int dimension;  // Liczba nodeow (miasta + depot)
    int depotId;    // Indeks node ktory jest depotem

    void calculateDistances();

public:
    Problem();

    int getCapacity() const { return capacity; }
    int getNumberOfGroups() const { return numberOfGroups; }
    int getNumberOfClients() const { return dimension - 1; } // Klienci = punkty - depot
    int getDepotId() const { return depotId; }

    int getDemand(int nodeIndex) const;
    double getDistance(int node1, int node2) const;
    const std::vector<int>& getPermutation() const { return permutation; }
};

#endif //LAB6_PROBLEM_H