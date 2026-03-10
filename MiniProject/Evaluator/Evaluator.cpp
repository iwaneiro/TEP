//
// Created by Kuba Iwanicki on 19/01/2026.
//

#include "../Evaluator/Evaluator.h"
#include <fstream>
#include <iostream>
#include <sstream>

const double Evaluator::PENALTY_MULTIPLIER = 100.0;
const int Evaluator::DEFAULT_NUM_OF_TRUCKS = 5;
Evaluator::Evaluator() = default;

Result<void, Error> Evaluator::load(std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        return Result<void, Error>::fail("Nie znaleziono pliku: "+filename);
    }

    // Reset danych
    problem.nodes.clear();
    problem.demands.clear();
    problem.permutation.clear();
    problem.distances.clear();
    problem.capacity = 0;
    problem.numberOfGroups = 0;
    problem.dimension = 0;
    problem.depotId = 0;

    std::string line;
    std::string section;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string keyword;

        if (line.find("DIMENSION") != std::string::npos) {
            std::string trash;
            ss >> keyword >> trash >> problem.dimension;

            if (problem.dimension <= 0) {
                return Result<void, Error>::fail("DIMENSION musi byc > 0");
            }
            problem.nodes.reserve(problem.dimension);
            problem.demands.reserve(problem.dimension);
            problem.permutation.reserve(problem.dimension - 1);
        }
        else if (line.find("CAPACITY") != std::string::npos) {
            std::string trash;
            ss >> keyword >> trash >> problem.capacity;
            if (problem.capacity <= 0) {
                return Result<void, Error>::fail("CAPACITY musi byc > 0");
            }
        }
        else if (line.find("NAME") != std::string::npos) {
            std::string phrase = "-k";
            size_t pos = line.find(phrase);
            if (pos != std::string::npos) {
                try {
                    std::stringstream ss_trucks(line.substr(pos + phrase.length()));
                    ss_trucks >> problem.numberOfGroups;
                } catch (...) {
                }
            }
        }
        else if (line.find("PERMUTATION") != std::string::npos) {
            std::string trash;
            ss >> keyword;
            if (line.find(':') != std::string::npos) ss >> trash;

            int id;
            while (ss >> id) {
                problem.permutation.push_back(id - 1);
            }
            continue;
        }
        else if (line.find("NODE_COORD_SECTION") != std::string::npos) {
            section = "COORD";
            continue;
        }
        else if (line.find("DEMAND_SECTION") != std::string::npos) {
            section = "DEMAND";
            continue;
        }
        else if (line.find("DEPOT_SECTION") != std::string::npos) {
            section = "DEPOT";
            continue;
        }
        else if (line.find("EOF") != std::string::npos) {
            break;
        }

        if (!section.empty()) {
            if (section == "COORD") {
                int id;
                double x, y;
                if (ss >> id >> x >> y) {
                    problem.nodes.push_back({id, x, y});
                } else {
                    return Result<void, Error>::fail("[FILE ERROR] nie udało się wczytac sekcji: " + section);
                }
            }
            else if (section == "DEMAND") {
                int id, demand;
                if (ss >> id >> demand) {
                    problem.demands.push_back(demand);
                } else {
                    return Result<void, Error>::fail("[FILE ERROR] nie udało się wczytac sekcji: " + section);
                }
            }
            else if (section == "DEPOT") {
                int id;
                if (ss >> id) {
                    if (id != -1) {
                        problem.depotId = id - 1;
                    } else {
                        section = "";
                    }
                } else {
                    return Result<void, Error>::fail("[FILE ERROR] nie udało się wczytac sekcji: " + section);
                }
            }
        }
    }
    file.close();

    if (problem.nodes.size() != (size_t)problem.dimension) {
        return Result<void, Error>::fail("[FILE ERROR] Wczytana liczba wezlow nie zgadza sie z DIMENSION.");
    }
    if (problem.demands.size() != (size_t)problem.dimension) {
        return Result<void, Error>::fail("[FILE ERROR] Wczytana liczba zapotrzebowan nie zgadza sie z DIMENSION.");
    }

    if (problem.permutation.size() != problem.dimension - 1) {
        return Result<void, Error>::fail("[FILE ERROR] Wczytana permutacja nie zgadza sie z DIMENSION.");
    }

    if (problem.capacity <= 0) {
        return Result<void, Error>::fail("[FILE ERROR] CAPACITY musi byc > 0");
    }

    if (problem.numberOfGroups <= 0) {
        problem.numberOfGroups = DEFAULT_NUM_OF_TRUCKS;
    }

    problem.calculateDistances();

    trucks.assign(problem.numberOfGroups, TruckState(problem.depotId));

    std::cout << "Wczytano problem: " << filename
              << "\nLiczba miast: " << problem.dimension
              << "\nLiczba cięzarówek (k): " << problem.numberOfGroups
              << "\nPojemnosc: " << problem.capacity << std::endl;

    return Result<void, Error>::success();
}

double Evaluator::evaluate(const std::vector<int> &genotype) const {
    int numTrucks = problem.getNumberOfGroups();
    int depotId = problem.getDepotId();
    int capacity = problem.getCapacity();

    for(int i=0; i<numTrucks; ++i) {
        trucks[i].reset(depotId);
    }

    double total_distance = 0.0;

    const std::vector<int>& permutation = problem.getPermutation();

    for (const int client_node_idx : permutation) {
        int gene_idx = client_node_idx - 1;

        int truck_idx = genotype[gene_idx];
        TruckState& truck = trucks[truck_idx];

        // Dojazd do klienta
        truck.current_distance += problem.getDistance(truck.previous_node_idx, client_node_idx);
        truck.current_load += problem.getDemand(client_node_idx);
        truck.previous_node_idx = client_node_idx;
    }

    // Powrót do bazy dla wszystkich ciezarowek
    for (const TruckState& truck : trucks) {
        double route_distance = truck.current_distance;
        // Powrót do depotu
        route_distance += problem.getDistance(truck.previous_node_idx, depotId);

        // Kara za przekroczenie capacity
        if (truck.current_load > capacity) {
            int overweight = truck.current_load - capacity;
            route_distance += overweight * PENALTY_MULTIPLIER;
        }
        total_distance += route_distance;
    }

    return total_distance;
}