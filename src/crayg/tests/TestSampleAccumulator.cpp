#include <catch2/catch.hpp>
#include "renderer/SampleAccumulator.h"

namespace crayg {

TEST_CASE("SampleAccumulator::getValue") {
    SampleAccumulator sampleAccumulator;

    SECTION("should return correct accumulated value") {
        auto testData = GENERATE(table<std::vector<Color>, Color>({{{Color::createWhite()}, {Color::createWhite()}},
                                                                   {{Color::createBlack(), Color::createWhite()},
                                                                    {Color::createGrey(0.5f)}},
                                                                   {{Color::createGrey(0.1f), Color::createGrey(0.5f),
                                                                     Color::createGrey(0.3f), Color::createGrey(0.9f),
                                                                     Color::createGrey(0.5f)},
                                                                    {Color::createGrey(0.45999998f)}}}));

        for (auto sample: std::get<0>(testData)) {
            sampleAccumulator.addSample(sample);
        }

        REQUIRE(sampleAccumulator.getValue() == std::get<1>(testData));
    }
}

}