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
    float r = std::sqrt(std::max((float)0, (float)1. - z * z));
    float phi = 2.0f * boost::math::constants::pi<float>() * v;
    return {r * std::cos(phi), z, r * std::sin(phi)};
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

Vector2f Sampling::concentricSampleDisk() {
    return concentricSampleDisk(Random::random(), Random::random());
}

Vector2f Sampling::concentricSampleDisk(float u, float v) {
    static float piOver4 = boost::math::constants::pi<float>() / 4;
    static float piOver2 = boost::math::constants::pi<float>() / 2;
    float uOffsetX = 2.f * u - 1;
    float uOffsetY = 2.f * v - 1;

    if (uOffsetX == 0 && uOffsetY == 0) {
        return {0, 0};
    }

    float theta, r;
    if (std::abs(uOffsetX) > std::abs(uOffsetY)) {
        r = uOffsetX;
        theta = piOver4 * (uOffsetY / uOffsetX);
    } else {
        r = uOffsetY;
        theta = piOver2 - piOver4 * (uOffsetX / uOffsetY);
    }
    return Vector2f(std::cos(theta), std::sin(theta)) * r;
}
} // crayg