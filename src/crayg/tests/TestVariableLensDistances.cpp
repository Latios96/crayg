#include "crayg/scene/camera/realistic/VariableLensDistances.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("VariableLensDistances::getFirstSampleIndex") {
    SampledDistance sampledDistance1;
    sampledDistance1.surfaceIndex = 0;
    sampledDistance1.samples.push_back(0);
    sampledDistance1.samples.push_back(1);
    SampledDistance sampledDistance2;
    sampledDistance2.surfaceIndex = 1;
    sampledDistance2.samples.push_back(2);
    sampledDistance2.samples.push_back(3);

    VariableLensDistances variableLensDistances;
    variableLensDistances.sampledFocalLengths.push_back(50);
    variableLensDistances.sampledFocalLengths.push_back(80);
    variableLensDistances.sampledDistances.push_back(sampledDistance1);
    variableLensDistances.sampledDistances.push_back(sampledDistance2);

    SECTION("should clamp min focal length correctly") {
        const auto indexAndWeight = variableLensDistances.getFirstSampleIndex(40);

        REQUIRE(indexAndWeight == IndexAndWeight(0, 0));
    }

    SECTION("should clamp min focal length correctly on edge") {
        const auto indexAndWeight = variableLensDistances.getFirstSampleIndex(50);

        REQUIRE(indexAndWeight == IndexAndWeight(0, 0));
    }

    SECTION("should clamp max focal length correctly") {
        const auto indexAndWeight = variableLensDistances.getFirstSampleIndex(90);

        REQUIRE(indexAndWeight == IndexAndWeight(0, 1));
    }

    SECTION("should clamp max focal length correctly on edge") {
        const auto indexAndWeight = variableLensDistances.getFirstSampleIndex(80);

        REQUIRE(indexAndWeight == IndexAndWeight(0, 1));
    }

    SECTION("should return correct index and weight for simple distance setup") {
        const auto indexAndWeight = variableLensDistances.getFirstSampleIndex(65);

        REQUIRE(indexAndWeight == IndexAndWeight(0, 0.5f));

        const float distance = variableLensDistances.sampledDistances[0].getDistance(indexAndWeight);
        REQUIRE(distance == 0.5);
    }

    SECTION("should return correct index and weight for complex distance setup") {
        variableLensDistances.sampledFocalLengths.push_back(100);
        variableLensDistances.sampledDistances[0].samples.push_back(2);
        variableLensDistances.sampledDistances[1].samples.push_back(4);

        const auto indexAndWeight_65mm = variableLensDistances.getFirstSampleIndex(65);
        REQUIRE(indexAndWeight_65mm == IndexAndWeight(0, 0.5f));
        const float distance_65mm = variableLensDistances.sampledDistances[0].getDistance(indexAndWeight_65mm);
        REQUIRE(distance_65mm == 0.5);

        const auto indexAndWeight_90mm = variableLensDistances.getFirstSampleIndex(90);
        REQUIRE(indexAndWeight_90mm == IndexAndWeight(1, 0.5f));
        const float distance_90mm = variableLensDistances.sampledDistances[0].getDistance(indexAndWeight_90mm);
        REQUIRE(distance_90mm == 1.5);
    }
}

}