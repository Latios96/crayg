#include "Sampling.h"
#include "Random.h"
#include <boost/math/constants/constants.hpp>

namespace crayg {
Vector3f Sampling::uniformSampleHemisphere() {
    return uniformSampleHemisphere(Random::random(), Random::random());
}
// based on PBRT-V3
Vector3f Sampling::uniformSampleHemisphere(float u, float v) {
    float z = u;
    float r = std::sqrt(std::max((float) 0, (float) 1. - z * z));
    float phi = 2 * boost::math::constants::pi<double>() * v;
    return {r * std::cos(phi), r * std::sin(phi), z};

}
Vector3f Sampling::uniformSampleSphere() {
    return uniformSampleSphere(Random::random(), Random::random());
}
// based on PBRT-V3
Vector3f Sampling::uniformSampleSphere(float u, float v) {
    float z = 1 - 2 * u;
    float r = std::sqrt(std::max(0.f, 1.f - z * z));
    float phi = 2.0f * boost::math::constants::pi<float>() * v;
    return {r * std::cos(phi), r * std::sin(phi), z};

}
} // crayg