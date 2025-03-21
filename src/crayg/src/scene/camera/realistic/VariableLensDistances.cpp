#include "VariableLensDistances.h"
#include "utils/ToStringHelper.h"

namespace crayg {

IndexAndWeight::IndexAndWeight(int firstSampleIndex, float t) : firstSampleIndex(firstSampleIndex), weight(t) {
}

bool IndexAndWeight::operator==(const IndexAndWeight &rhs) const {
    return firstSampleIndex == rhs.firstSampleIndex && weight == rhs.weight;
}

bool IndexAndWeight::operator!=(const IndexAndWeight &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const IndexAndWeight &indexAndWheight) {
    os << ToStringHelper("IndexAndWeight")
              .addMember("firstSampleIndex", indexAndWheight.firstSampleIndex)
              .addMember("weight", indexAndWheight.weight)
              .finish();
    return os;
}

float SampledDistance::getDistance(const IndexAndWeight &indexAndWeight) const {
    return getDistance(indexAndWeight.firstSampleIndex, indexAndWeight.weight);
}

float SampledDistance::getDistance(int firstSampleIndex, float t) const {
    const auto firstSample = samples[firstSampleIndex];
    const auto secondSample = samples[firstSampleIndex + 1];
    return MathUtils::lerp(t, firstSample, secondSample);
}

SampledDistance::SampledDistance(int surfaceIndex, const std::vector<float> &samples)
    : surfaceIndex(surfaceIndex), samples(samples) {
}
}