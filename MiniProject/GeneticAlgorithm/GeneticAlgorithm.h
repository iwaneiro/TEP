//
// Created by Kuba Iwanicki on 19/01/2026.
//

#ifndef LAB6_GENETICALGORITHM_H
#define LAB6_GENETICALGORITHM_H

#include <random>
#include <vector>
#include "../SmartPtr.h"
#include "../Individual/Individual.h"
#include "../Evaluator/Evaluator.h"

class GeneticAlgorithm {
private:
    int popSize;
    double crossProb;
    double mutProb;
    int iterations;
    std::mt19937 rng;

    Evaluator evaluator;
    std::vector<SmartPtr<Individual>> population;

    void initializePopulation();
    SmartPtr<Individual> selectParent();
public:
    GeneticAlgorithm(int popSize, double crossProb, double mutProb, int iterations);
    Result<void, Error> loadProblem(std::string &filename);
    Result<void, Error> run(int printFreq);
};


#endif //LAB6_GENETICALGORITHM_H