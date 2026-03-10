#include <iostream>
#include "GeneticAlgorithm/GeneticAlgorithm.h"

int main() {
    std::string inputFile = "../data/lcvrp/Vrp-Set-A/A-n32-k5.lcvrp";

    GeneticAlgorithm ag(300, 0.85, 0.015, 10000);

    Result<void, Error> result = ag.loadProblem(inputFile);

    if (result.isSuccess()) {
        ag.run(1000);
    } else {
        std::cerr << result.getErrorMessage() << std::endl;
    }

    return 0;
}