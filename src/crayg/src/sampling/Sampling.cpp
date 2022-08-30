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
} // crayg