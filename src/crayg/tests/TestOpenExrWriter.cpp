#include <boost/filesystem.hpp>
#include <catch2/catch.hpp>
#include <image/Image.h>
#include <image/imageiterators/pixels/ImageIterators.h>
#include <image/io/OpenExrWriter.h>

namespace crayg {

TEST_CASE("OpenExrWriter") {
    Image image(20, 10);
    OpenExrWriter openExrWriter;

    for (auto p : ImageIterators::lineByLine(image)) {
        image.setValue(p, Color::createGrey(static_cast<float>(p.x) / static_cast<float>(image.getWidth())));
    }

    if (boost::filesystem::exists("OpenExrWriter.png")) {
        REQUIRE(remove("OpenExrWriter.png") == 0);
    }

    openExrWriter.writeImage(image, "OpenExrWriter.png");
    REQUIRE(boost::filesystem::exists("OpenExrWriter.png"));

    if (boost::filesystem::exists("testImage.png")) {
        REQUIRE(remove("testImage.png") == 0);
    }
}

}
