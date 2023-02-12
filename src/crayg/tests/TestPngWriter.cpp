#include <catch2/catch.hpp>
#include <image/Image.h>
#include <boost/filesystem.hpp>
#include <image/PngWriter.h>
#include <image/ImageIterators.h>

namespace crayg {

TEST_CASE("PngWriter") {
    Image image(20, 10);
    PngWriter pngWriter;

    for (auto p: ImageIterators::lineByLine(image)) {
        image.setValue(p.x, p.y, Color::createGrey(static_cast<float>(p.x) / static_cast<float>(image.getWidth())));
    }

    if (boost::filesystem::exists("PngWriter.png")) {
        REQUIRE(remove("PngWriter.png") == 0);
    }

    pngWriter.writeImage(image, "PngWriter.png");
    REQUIRE(boost::filesystem::exists("PngWriter.png"));

    if (boost::filesystem::exists("testImage.png")) {
        REQUIRE(remove("testImage.png") == 0);
    }
}

}
