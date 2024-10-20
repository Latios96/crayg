#include "fixtures/TemporaryDirectory.h"
#include "fixtures/UnitPlaneUvs.h"
#include "image/Image.h"
#include "image/ImageAlgorithms.h"
#include "image/io/ImageWriters.h"
#include "scene/primitives/Sphere.h"
#include "scene/shadingnetworks/shadingnodes/FileTexture.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("TestFileTexture::evaluateColor") {
    auto sphere = std::make_shared<Sphere>();
    auto unitPlaneUvs = std::make_shared<UnitPlaneUvs>();
    FileTexture fileTexture;
    fileTexture.uvInput.connectTo(unitPlaneUvs);
    fileTexture.fallbackColor = Color(1, 0, 0);

    SECTION("should use texture") {
        TemporaryDirectory temporaryDirectory;
        const std::string texturePath = temporaryDirectory.getFilePath("blue.exr");
        fileTexture.setFilePath(texturePath);
        fileTexture.colorSpace = FileTexture::ColorSpace::RAW;
        Image image(10, 10);
        ImageAlgorithms::fill(image, Color(0, 1, 0));
        ImageWriters::writeImage(image, texturePath);

        auto color = fileTexture.evaluateColor(SurfaceInteraction(*sphere, {0.5, 0.5, 0}, {}, {}));

        REQUIRE(color == Color(0, 1, 0));
    }

    SECTION("should fall back to fallback color if file not found") {
        auto color = fileTexture.evaluateColor(SurfaceInteraction(*sphere, {0, 0, 0}, {}, {}));

        REQUIRE(color == Color(1, 0, 0));
    }
}

}