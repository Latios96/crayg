#include <catch2/catch.hpp>
#include <image/Image.h>
#include <image/BmpImageWriter.h>
#include "fixtures/TemporaryDirectory.h"

namespace crayg {

static const std::string TEST_IMAGE_NAME = "testImageWrite.bmp";

TEST_CASE("BmpImageWriter") {
    Image image(20, 10);
    BmpImageWriter writer;

    TemporaryDirectory temporaryDirectory;
    boost::filesystem::path imagePath = temporaryDirectory.getPath() / TEST_IMAGE_NAME;

    SECTION("fileShouldExistAfterWrite") {
        writer.writeImage(image, imagePath.string());
        REQUIRE(boost::filesystem::exists(imagePath));
    }
}

}