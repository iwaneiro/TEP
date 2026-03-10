//
// Created by Kuba Iwanicki on 19/01/2026.
//

#ifndef LAB6_RANDOMUTILS_H
#define LAB6_RANDOMUTILS_H
#include <random>

class RandomUtils {
    public:

    static int getInt(int min, int max, std::mt19937& rng) {
        std::uniform_int_distribution<> dis(min, max);
        return dis(rng);
    }

    static double getDouble(double min, double max, std::mt19937& rng) {
        std::uniform_real_distribution<> dis(min, max);
        return dis(rng);
    }
};


#endif //LAB6_RANDOMUTILS_H