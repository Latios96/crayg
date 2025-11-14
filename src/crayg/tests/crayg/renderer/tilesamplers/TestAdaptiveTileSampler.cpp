#include "crayg/renderer/tilesamplers/AdaptiveTileSampler.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("AdaptiveTileSampler::addRequiredImageSpecs") {

    SECTION("should add required image channels") {
        AdaptiveTileSampler adaptiveTileSampler(
            4, [](Vector2f samplePos) { return Color::createWhite(); }, 8, 0.007f);

        ImageTile imageTile(Tile({0, 0}, 5, 5));
        ImageSpecBuilder builder(Resolution::deduce(imageTile.tile));
        adaptiveTileSampler.addRequiredImageSpecs(builder);
        auto imageSpec = builder.finish();

        REQUIRE(imageSpec.channels ==
                std::vector<ChannelSpec>({{"rgb", PixelFormat::FLOAT32, 3}, {"sampleCount", PixelFormat::FLOAT32, 3}}));
    }
}

TEST_CASE("AdaptiveTileSampler::shouldTerminate") {
    AdaptiveTileSampler adaptiveTileSampler(
        4, [](Vector2f samplePos) { return Color::createWhite(); }, 8, 0.007f);

    SECTION("should return false if error is larger than max error and max samples are not reached") {
        auto shouldTerminate = adaptiveTileSampler.shouldTerminate(2, 0.1f);

        REQUIRE_FALSE(shouldTerminate);
    }

    SECTION("should return false if error is smaller than max error and min samples are not reached") {
        auto shouldTerminate = adaptiveTileSampler.shouldTerminate(2, 0.001f);

        REQUIRE_FALSE(shouldTerminate);
    }

    SECTION(
        "should return true if error is smaller than max error, min samples are reached max samples are not reached") {
        auto shouldTerminate = adaptiveTileSampler.shouldTerminate(5, 0.001f);

        REQUIRE(shouldTerminate);
    }

    SECTION("should return false if error is larger than max error and max samples are reached") {
        auto shouldTerminate = adaptiveTileSampler.shouldTerminate(17, 0.1f);

        REQUIRE(shouldTerminate);
    }

    SECTION("should return false if error is larger than max error, min samples are reached, but max samples are not "
            "reached") {
        AdaptiveTileSampler adaptiveTileSampler(
            1024, [](Vector2f samplePos) { return Color::createWhite(); }, 8, 0.007f);

        auto shouldTerminate = adaptiveTileSampler.shouldTerminate(128, 0.1f);

        REQUIRE_FALSE(shouldTerminate);
    }
}

TEST_CASE("AdaptiveTileSampler::minSamples") {

    SECTION("should calculate min samples correctly") {
        auto testData = GENERATE(table<float, int, int>(
            {{0.1, 1, 1024}, {0.04, 1, 1024}, {0.01, 1, 1024}, {0.001, 1, 1024}, {0.001, 16, 16}}));
        auto maxError = std::get<0>(testData);
        auto minSamples = std::get<1>(testData);
        auto maxSamples = std::get<1>(testData);

        AdaptiveTileSampler adaptiveTileSampler(
            maxSamples, [](Vector2f samplePos) { return Color::createWhite(); }, 8, maxError);

        REQUIRE(adaptiveTileSampler.getMinSamples() == minSamples);
    }
}

TEST_CASE("AdaptiveTileSampler::evaluateErrorMetric") {
    AdaptiveTileSampler adaptiveTileSampler(
        4, [](Vector2f samplePos) { return Color::createWhite(); }, 8, 0.007f);

    SECTION("should return 0 if fully sampled color is nan") {
        const float error =
            adaptiveTileSampler.evaluateErrorMetric(Color::createGrey(std::nan("")), Color::createWhite());

        REQUIRE(error == 0);
    }

    SECTION("should return 0 if half sampled color is nan") {
        const float error =
            adaptiveTileSampler.evaluateErrorMetric(Color::createWhite(), Color::createGrey(std::nan("")));

        REQUIRE(error == 0);
    }

    SECTION("should return 0 if fullySampled color is black") {
        const float error = adaptiveTileSampler.evaluateErrorMetric(Color::createBlack(), Color::createWhite());

        REQUIRE(error == 0);
    }

    SECTION("should return the calculated error") {
        const float error = adaptiveTileSampler.evaluateErrorMetric(Color(0.1f, 0.2f, 0.3f), Color(0.4f, 0.5f, 0.6f));

        REQUIRE(error == Catch::Detail::Approx(1.1619f));
    }
}

}