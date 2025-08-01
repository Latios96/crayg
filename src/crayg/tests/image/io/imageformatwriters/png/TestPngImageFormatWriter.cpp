
#include "fixtures/TemporaryDirectory.h"
#include "image/Image.h"
#include "image/imageiterators/pixels/ImageIterators.h"
#include "image/io/imageformatwriters/png/PngImageFormatWriter.h"
#include <lodepng.h>
#include <map>

#include <catch2/catch.hpp>

namespace crayg {

struct PngAsserter {
    PngAsserter(const std::filesystem::path &path) {
        if (!std::filesystem::exists(path)) {
            CRAYG_LOG_AND_THROW_RUNTIME_ERROR("File {} does not exist", path);
        }
        std::vector<unsigned char> png;
        std::vector<unsigned char> image;
        unsigned width, height;

        unsigned error = lodepng::load_file(png, reinterpret_cast<const char *>(path.u8string().c_str()));
        if (error) {
            CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Error when encoding PNG image at path {}: {}", path,
                                              lodepng_error_text(error));
        }

        error = lodepng::decode(image, width, height, state, png);
        if (error) {
            CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Error when encoding PNG image at path {}: {}", path,
                                              lodepng_error_text(error));
        }

        for (int i = 0; i < state.info_png.text_num; i++) {
            text[state.info_png.text_keys[i]] = state.info_png.text_strings[i];
        }
    }

    LodePNGColorType getColorType() {
        return state.info_png.color.colortype;
    }

    std::string getText(const std::string &key) {
        if (text.find(key) == text.end()) {
            CRAYG_LOG_AND_THROW_RUNTIME_ERROR("PNG file has no text for key '{}'", key);
        }
        return text[key];
    }

    lodepng::State state;
    std::map<std::string, std::string> text;
};

struct ImageFixture {
    Image image;

    ImageFixture() : image(Image(128, 72)) {
    }

    void addTestMetadata() {
        image.metadata.write("test/int", 42);
        image.metadata.write("test/float", 42.42f);
        image.metadata.write("test/string", "teststring");
        image.metadata.write("test/seconds", std::chrono::seconds(42));
    }
};

TEST_CASE("PngImageFormatWriter::write Image") {
    // create fixtures here, reuse them for integration tests
    // check data format is as expected
    // check metadata is written

    PngImageFormatWriter pngImageFormatWriter;
    TemporaryDirectory temporaryDirectory;
    const std::filesystem::path imagePath = temporaryDirectory.getFilePath("testimage.png");

    SECTION("should write rgb float image") {
        ImageFixture imageFixture;
        // todo extract this
        for (auto pixel : ImageIterators::lineByLine(imageFixture.image)) {
            const float relativeX = static_cast<float>(pixel.x) / imageFixture.image.getWidth();
            const float relativeY = static_cast<float>(pixel.y) / imageFixture.image.getHeight();
            if (relativeY <= 0.33) {
                imageFixture.image.setValue(pixel, Color(relativeX, 0, 0));
            } else if (relativeY <= 0.66) {
                imageFixture.image.setValue(pixel, Color(0, relativeX, 0));
            } else {
                imageFixture.image.setValue(pixel, Color(0, 0, relativeX));
            }
        }

        imageFixture.image.setValue({0, 0}, {0.1, 0.2, 0.3});
        imageFixture.addTestMetadata();

        pngImageFormatWriter.write(imagePath, imageFixture.image);

        PngAsserter pngAsserter(imagePath);

        // todo verify this is an 8 bit file
        REQUIRE(pngAsserter.getColorType() == LodePNGColorType::LCT_RGB);
        // todo extract this
        REQUIRE(pngAsserter.getText("test/int") == "42");
        REQUIRE(pngAsserter.getText("test/float") == "42.42");
        REQUIRE(pngAsserter.getText("test/string") == "teststring");
        REQUIRE(pngAsserter.getText("test/seconds") == "42s");
    }

    SECTION("should write image with grey int custom channel") {
        // verify the two files exist
        // verify second file has grey type
        // verify both files have the metadata
    }

    SECTION("should write image with grey float custom channel") {
    }

    SECTION("should write image with rgb int custom channel") {
    }

    SECTION("should write image with rgb int custom channel") {
    }

    SECTION("should write image with empty metadata") {
    }

    SECTION("should ignore specified render region") {
    }
}

// todo same tests for film

}