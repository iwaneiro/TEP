//
// Created by Kuba Iwanicki on 19/01/2026.
//

#include "../GeneticAlgorithm/GeneticAlgorithm.h"
#include "../RandomUtils.h"
#include <iostream>
#include <limits>

GeneticAlgorithm::GeneticAlgorithm(int popSize, double crossProb, double mutProb, int iterations)
    : popSize(popSize), crossProb(crossProb), mutProb(mutProb), iterations(iterations), rng(std::random_device{}()) {}

Result<void, Error> GeneticAlgorithm::loadProblem(std::string &filename) {
    return evaluator.load(filename);
}

void GeneticAlgorithm::initializePopulation() {
    population.clear();
    int genotypeSize = evaluator.getGenotypeSize();
    int groups = evaluator.getNumberOfGroups();

    for (int i = 0; i < popSize; ++i) {
        SmartPtr<Individual> ind(new Individual(genotypeSize, groups, rng));
        ind->calculateFitness(evaluator);
        population.push_back(ind);
    }
}

SmartPtr<Individual> GeneticAlgorithm::selectParent() {
    int idx1 = RandomUtils::getInt(0, popSize - 1, rng);
    int idx2 = RandomUtils::getInt(0, popSize - 1, rng);

    if (population[idx1]->getFitness() < population[idx2]->getFitness()) {
        return population[idx1];
    }
    return population[idx2];
}

Result<void, Error> GeneticAlgorithm::run(int printFreq) {
    if (evaluator.getGenotypeSize()<=0) {
        return Result<void, Error>::fail("[ERROR] Nie wczytano problemu!");
    }
    initializePopulation();

    SmartPtr<Individual> bestSolution;
    double bestFitness = std::numeric_limits<double>::max();

    for (int it = 0; it < iterations; ++it) {
        std::vector<SmartPtr<Individual>> newPop;

        while (newPop.size() < popSize) {
            SmartPtr<Individual> parent1 = selectParent();
            SmartPtr<Individual> parent2 = selectParent();

            std::pair<SmartPtr<Individual>, SmartPtr<Individual>> children = parent1->crossover(*parent2, crossProb, rng);

            children.first->mutate(mutProb, evaluator.getNumberOfGroups(), rng);
            children.first->calculateFitness(evaluator);

            children.second->mutate(mutProb, evaluator.getNumberOfGroups(), rng);
            children.second->calculateFitness(evaluator);

            newPop.push_back(std::move(children.first));
            if (newPop.size() < popSize) newPop.push_back(std::move(children.second));
        }
        population = newPop;

        for (int i = 0; i < popSize; ++i) {
            if (population[i]->getFitness() < bestFitness) {
                bestFitness = population[i]->getFitness();

                bestSolution = SmartPtr<Individual>(new Individual(population[i]->getGenotype()));
                bestSolution->calculateFitness(evaluator);
            }
        }
        if (it % printFreq == 0 || it == iterations-1) {
            std::cout << "It: " << it << " Best Fitness: "<< bestFitness <<std::endl;
        }
    }
    std::cout << "--- KONIEC ---" << std::endl;
    if (!bestSolution.isNull()) {
        std::cout << "Genotyp: ";
        bestSolution->printGenotype();
    }
    return Result<void, Error>::success();
}
