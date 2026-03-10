//
// Created by Kuba Iwanicki on 19/01/2026.
//

#ifndef LAB6_EVALUATOR_H
#define LAB6_EVALUATOR_H

#include <vector>

#include "../Result.h"
#include "../Problem/Problem.h"
#include "../Error/Error.h"

class Evaluator {
private:
    Problem problem;

    struct TruckState {
        int previous_node_idx;  // Gdzie ciezarowka byla ostatnio
        double current_distance;
        int current_load;

        TruckState() : previous_node_idx(0), current_distance(0.0), current_load(0) {}
        explicit TruckState(int depot_id) : previous_node_idx(depot_id), current_distance(0.0), current_load(0) {}

        void reset(int depot_id) {
            previous_node_idx = depot_id;
            current_distance = 0.0;
            current_load = 0;
        }
    };

    mutable std::vector<TruckState> trucks;
    static const double PENALTY_MULTIPLIER;


public:
    static const int DEFAULT_NUM_OF_TRUCKS;

    Evaluator();

    Result<void, Error> load(std::string& filename);
    double evaluate(const std::vector<int>& genotype) const;

    int getGenotypeSize() const { return problem.getNumberOfClients(); }
    int getNumberOfGroups() const { return problem.getNumberOfGroups(); }
};

#endif //LAB6_EVALUATOR_H