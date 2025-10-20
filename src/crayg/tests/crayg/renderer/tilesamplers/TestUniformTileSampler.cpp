#include "crayg/renderer/tilesamplers/UniformTileSampler.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("UniformTileSampler::addRequiredImageSpecs") {

    SECTION("should add required image channels") {
        UniformTileSampler uniformTileSampler(4, [](Vector2f samplePos) { return Color::createWhite(); });

        ImageTile imageTile(Tile({0, 0}, 5, 5));
        ImageSpecBuilder builder(Resolution::deduce(imageTile.tile));
        uniformTileSampler.addRequiredImageSpecs(builder);
        auto imageSpec = builder.finish();

        REQUIRE(imageSpec.channels == std::vector<ChannelSpec>({{"rgb", PixelFormat::FLOAT32, 3}}));
    }
}

}