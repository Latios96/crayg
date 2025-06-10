#pragma once

#include "basics/math/CommonMath.h"
#include <ostream>
#include <vector>

namespace crayg {

struct IndexAndWeight {
    int firstSampleIndex;
    float weight;

    IndexAndWeight() = default;
    IndexAndWeight(int firstSampleIndex, float t);

    bool operator==(const IndexAndWeight &rhs) const;
    bool operator!=(const IndexAndWeight &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const IndexAndWeight &weight);
};

struct SampledDistance {
    int surfaceIndex;
    std::vector<float> samples;

    SampledDistance() = default;
    SampledDistance(int surfaceIndex, const std::vector<float> &samples);

    float getDistance(const IndexAndWeight &indexAndWeight) const;
    float getDistance(int firstSampleIndex, float t) const;

    bool operator==(const SampledDistance &rhs) const;
    bool operator!=(const SampledDistance &rhs) const;
};

struct VariableLensDistances {
    std::vector<SampledDistance> sampledDistances;
    std::vector<float> sampledFocalLengths;

    float getMinFocalLength() const {
        return sampledFocalLengths.front();
    }

    float getMaxFocalLength() const {
        return sampledFocalLengths.back();
    }

    bool empty() const {
        return sampledDistances.empty();
    }

    IndexAndWeight getFirstSampleIndex(float focalLength) {
        const float minFocalLength = getMinFocalLength();
        const float maxFocalLength = getMaxFocalLength();

        if (focalLength <= minFocalLength) {
            return {0, 0};
        }
        if (focalLength >= maxFocalLength) {
            return {((int)sampledFocalLengths.size()) - 2, 1};
        }

        int firstSampleIndex = 0;
        for (int i = 0; i < sampledFocalLengths.size(); i++) {
            const auto sampledFocalLength = sampledFocalLengths[i];
            if (focalLength > sampledFocalLength) {
                firstSampleIndex = i;
            }
        }

        const auto firstSample = sampledFocalLengths[firstSampleIndex];
        const auto secondSample = sampledFocalLengths[firstSampleIndex + 1];

        const float n = focalLength - firstSample;
        const float m = secondSample - firstSample;
        const float t = n / m;

        return {firstSampleIndex, t};
    }
};

}