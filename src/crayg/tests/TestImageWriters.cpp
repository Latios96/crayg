#include "fixtures/TemporaryDirectory.h"
#include <boost/filesystem.hpp>
#include <catch2/catch.hpp>
#include <fstream>
#include <image/Image.h>
#include <image/io/ImageWriters.h>

namespace crayg {

TEST_CASE("ImageWriters/ImageWriterType") {
    Image image(20, 10);

    SECTION("PNG") {
        TemporaryDirectory temporaryDirectory;
        const std::string pngPath = temporaryDirectory.getFilePath("ImageWriters_png.png");

        REQUIRE(ImageWriters::writeImage(image, pngPath));
        REQUIRE(boost::filesystem::exists(pngPath));
    }

    SECTION("EXR") {
        TemporaryDirectory temporaryDirectory;
        const std::string exrPath = temporaryDirectory.getFilePath("ImageWriters_exr.png");

        REQUIRE(ImageWriters::writeImage(image, exrPath));
        REQUIRE(boost::filesystem::exists(exrPath));
    }

    SECTION("unknown") {
        TemporaryDirectory temporaryDirectory;
        const std::string unknownFormatPath = temporaryDirectory.getFilePath("ImageWriters_unknown.unknown");
        REQUIRE_THROWS_AS(ImageWriters::writeImage(image, unknownFormatPath), std::runtime_error);
        REQUIRE_FALSE(boost::filesystem::exists(unknownFormatPath));
    }
}

}
