//
// Created by Kuba Iwanicki on 19/01/2026.
//

#include "../Problem/Problem.h"
#include <fstream>
#include <cmath>

Problem::Problem() : capacity(0), numberOfGroups(0), dimension(0), depotId(0) {}

void Problem::calculateDistances() {
    distances.resize(dimension * dimension);
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (i == j) {
                distances[i * dimension + j] = 0.0;
            } else {
                double dx = nodes[i].x - nodes[j].x;
                double dy = nodes[i].y - nodes[j].y;
                distances[i * dimension + j] = std::sqrt(dx * dx + dy * dy);
            }
        }
    }
}

int Problem::getDemand(int nodeIndex) const {
    if (nodeIndex >= 0 && nodeIndex < demands.size()) return demands[nodeIndex];
    return 0;
}

double Problem::getDistance(int node1, int node2) const {
    return distances[node1 * dimension + node2];
}