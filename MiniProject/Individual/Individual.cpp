//
// Created by Kuba Iwanicki on 19/01/2026.
//

#include "../Individual/Individual.h"
#include <iostream>
#include "../RandomUtils.h"

Individual::Individual(int genotypeSize, int numberOfGroups, std::mt19937& rng) {
    isEvaluated = false;
    fitness = 0;
    genotype.resize(genotypeSize);
    for (int i = 0; i < genotypeSize; ++i) {
        genotype[i] = RandomUtils::getInt(0, numberOfGroups - 1, rng);
    }
}

// Konstruktor dziecka
Individual::Individual(const std::vector<int> &newGenotype) {
    genotype = newGenotype;
    isEvaluated = false;
    fitness = 0.0;
}

void Individual::calculateFitness(const Evaluator &evaluator) {
    if (!isEvaluated) {
        fitness = evaluator.evaluate(genotype);
        isEvaluated = true;
    }
}

double Individual::getFitness() const {
    return fitness;
}

void Individual::mutate(double mutProb, int numberOfGroups, std::mt19937& rng) {
    for (size_t i = 0; i < genotype.size(); ++i) {
        if (RandomUtils::getDouble(0,1, rng) <mutProb) {
            // Zmiana ciezarowki na losowa
            genotype[i] = RandomUtils::getInt(0, numberOfGroups - 1, rng);
            isEvaluated = false; // Fitness jest nieaktualny
        }
    }
}

std::pair<SmartPtr<Individual>, SmartPtr<Individual>> Individual::crossover(Individual &other, double crossProb, std::mt19937& rng) {
    if (RandomUtils::getDouble(0, 1, rng) >= crossProb) {
        return std::make_pair(
            SmartPtr<Individual>(new Individual(this->genotype)),
            SmartPtr<Individual>(new Individual(other.genotype))
        );
    }

    int size = this->genotype.size();
    if (size<2) {
        // Zbyt maly genotyp ns podzial
        return std::make_pair(
            SmartPtr<Individual>(new Individual(this->genotype)),
            SmartPtr<Individual>(new Individual(other.genotype))
        );
    }

    int splitPoint = RandomUtils::getInt(0, size - 1, rng);

    std::vector<int> childGen1;
    std::vector<int> childGen2;
    childGen1.reserve(size);
    childGen2.reserve(size);

    // Dziecko 1 = Rodzic1(part1) + Rodzic2(part2)
    // Dziecko 2 = Rodzic2(part1) + Rodzic1(part2)

    for (int i = 0; i < size; ++i) {
        if (i < splitPoint) {
            childGen1.push_back(this->genotype[i]);
            childGen2.push_back(other.genotype[i]);
        } else {
            childGen1.push_back(other.genotype[i]);
            childGen2.push_back(this->genotype[i]);
        }
    }

    return std::make_pair(
        SmartPtr<Individual>(new Individual(childGen1)),
        SmartPtr<Individual>(new Individual(childGen2))
        );
}

void Individual::printGenotype() const {
    for (int g : genotype) {
        std::cout << g << "";
    }
    std::cout << "\nFitness: "<< fitness << "\n" << std::endl;
}



