#include "fixtures/TemporaryDirectory.h"
#include <OpenImageIO/imageio.h>
#include <catch2/catch.hpp>
#include <filesystem>
#include <fstream>
#include <image/Image.h>
#include <image/io/ImageWriters.h>

namespace crayg {

void verifyImageMetadata(const std::string &path) {

    auto imageInput = OIIO::ImageInput::open(path);
    REQUIRE(imageInput);

    const OIIO::ImageSpec &spec = imageInput->spec();

    REQUIRE(spec.get_string_attribute("stringAttr") == "stringAttrValue");
    REQUIRE(spec.get_int_attribute("intAttr") == 42);
    REQUIRE(spec.get_float_attribute("floatAttr") == 42.f);
}

TEST_CASE("ImageWriters/ImageWriterType") {
    Image image(20, 10);
    image.metadata.write("stringAttr", "stringAttrValue");
    image.metadata.write("intAttr", 42);
    image.metadata.write("floatAttr", 42.f);

    SECTION("PNG") {
        TemporaryDirectory temporaryDirectory;
        const std::string pngPath = temporaryDirectory.getFilePath("ImageWriters_png.png");

        REQUIRE(ImageWriters::writeImage(image, pngPath));
        REQUIRE(std::filesystem::exists(pngPath));
        verifyImageMetadata(pngPath);
    }

    SECTION("EXR") {
        TemporaryDirectory temporaryDirectory;
        const std::string exrPath = temporaryDirectory.getFilePath("ImageWriters_exr.png");

        REQUIRE(ImageWriters::writeImage(image, exrPath));
        REQUIRE(std::filesystem::exists(exrPath));
        verifyImageMetadata(exrPath);
    }

    SECTION("unknown") {
        TemporaryDirectory temporaryDirectory;
        const std::string unknownFormatPath = temporaryDirectory.getFilePath("ImageWriters_unknown.unknown");
        REQUIRE_THROWS_AS(ImageWriters::writeImage(image, unknownFormatPath), std::runtime_error);
        REQUIRE_FALSE(std::filesystem::exists(unknownFormatPath));
    }
}

}
