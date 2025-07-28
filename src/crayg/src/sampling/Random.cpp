#include "Random.h"
#include <random>
#include <thread>

namespace crayg {
float Random::random() {
    static thread_local std::uniform_real_distribution<float> distribution(0.0, 1.0);
    static thread_local std::mt19937 generator(std::hash<std::thread::id>()(std::this_thread::get_id()));
    return distribution(generator);
}

Vector2f Random::randomVector2f() {
    return {Random::random(), Random::random()};
}
}