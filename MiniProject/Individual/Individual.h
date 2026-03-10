//
// Created by Kuba Iwanicki on 19/01/2026.
//

#ifndef LAB6_INDIVIDUAL_H
#define LAB6_INDIVIDUAL_H

#include <random>
#include <vector>
#include "../SmartPtr.h"
#include "../Evaluator/Evaluator.h"

class Individual {
private:
    std::vector<int> genotype;
    double fitness;
    bool isEvaluated;

public:
    Individual(int genotypeSize, int numberOfGroups, std::mt19937& rng);
    explicit Individual(const std::vector<int>& newGenotype);

    void calculateFitness(const Evaluator& evaluator);
    double getFitness() const;

    void mutate(double mutProb, int numberOfGroups, std::mt19937& rng);

    std::pair<SmartPtr<Individual>, SmartPtr<Individual>> crossover(
        Individual& other,
        double crossProb,
        std::mt19937& rng
        );

    void printGenotype() const;
    const std::vector<int>& getGenotype() const {return genotype;};
};


#endif //LAB6_INDIVIDUAL_H