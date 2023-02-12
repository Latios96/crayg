#include <catch2/catch.hpp>
#include <image/Image.h>
#include <boost/filesystem.hpp>
#include <image/PngWriter.h>
#include <image/ImageIterators.h>
#include "fixtures/TemporaryDirectory.h"

namespace crayg {

TEST_CASE("PngWriter") {
    Image image(20, 10);
    PngWriter pngWriter;

    for (auto p: ImageIterators::lineByLine(image)) {
        image.setValue(p.x, p.y, Color::createGrey(static_cast<float>(p.x) / static_cast<float>(image.getWidth())));
    }

    SECTION("should write PNG with rgb only") {
        TemporaryDirectory temporaryDirectory;
        auto targetPathRgb = (temporaryDirectory.getPath() / "PngWriter.png").string();

        pngWriter.writeImage(image, targetPathRgb);

        REQUIRE(boost::filesystem::exists(targetPathRgb));
    }

    SECTION("should write PNG with rgb, alpha and depth") {
        image.addAlphaChannel();
        image.addDepthChannel();
        TemporaryDirectory temporaryDirectory;
        auto targetPathRgb = (temporaryDirectory.getPath() / "PngWriter.png").string();
        auto targetPathAlpha = (temporaryDirectory.getPath() / "PngWriter.alpha.png").string();
        auto targetPathDepth = (temporaryDirectory.getPath() / "PngWriter.depth.png").string();

        pngWriter.writeImage(image, targetPathRgb);

        REQUIRE(boost::filesystem::exists(targetPathRgb));
        REQUIRE(boost::filesystem::exists(targetPathAlpha));
        REQUIRE(boost::filesystem::exists(targetPathDepth));
    }

}

}
