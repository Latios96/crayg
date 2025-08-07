#include "ImageAndFilmFixture.h"
#include "compatibility/lodepng/fmt/LodePNG_formatter.h"
#include "crayg/foundation/areaiterators/AreaIterators.h"
#include "image/io/imageformatwriters/ImageFormatWriters.h"
#include "utils.h"
#include <catch2/catch.hpp>
#include <lodepng.h>
#include <map>

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

    bool hasNoText() const {
        return text.empty();
    }

    void verifyPngHasExpectedTestMetadata() {
        REQUIRE(getText("test/int") == "42");
        REQUIRE(getText("test/float") == "42.42");
        REQUIRE(getText("test/string") == "teststring");
        REQUIRE(getText("test/seconds") == "42s");
    }

    lodepng::State state;
    std::map<std::string, std::string> text;
};

void verifyPng(const std::filesystem::path &imagePath, LodePNGColorType expectedColorType,
               bool hasExpectedTestMetadata = true) {
    PngAsserter pngAsserter(imagePath);
    REQUIRE(pngAsserter.getColorType() == expectedColorType);
    if (hasExpectedTestMetadata) {
        pngAsserter.verifyPngHasExpectedTestMetadata();
    } else {
        REQUIRE(pngAsserter.hasNoText());
    }
}

std::string getImageFormatPngOutput(const std::string &testName) {
    return getOutputFilename("ImageFormatWriters", testName, ".png");
}

std::string getImageFormatPngOutput(const std::string &testName, const std::string &channelName) {
    return getOutputFilename("ImageFormatWriters", testName, fmt::format(".{}.png", channelName));
}

TEST_CASE("ImageFormatWriters/write_image_png_rgb_float") {
    ImageFixture imageFixture;
    const std::filesystem::path imagePath = getImageFormatPngOutput("write_image_png_rgb_float");

    ImageFormatWriters::write(imagePath, imageFixture.image);

    verifyPng(imagePath, LodePNGColorType::LCT_RGB);
}

TEST_CASE("ImageFormatWriters/write_image_png_customChannel_rgb_float") {
    ImageFixture imageFixture;
    imageFixture.addCustomChannel(PixelFormat::FLOAT32, 3);
    const std::filesystem::path imagePath = getImageFormatPngOutput("write_image_png_customChannel_rgb_float");

    ImageFormatWriters::write(imagePath, imageFixture.image);

    verifyPng(imagePath, LodePNGColorType::LCT_RGB);
    const std::filesystem::path customChannelPath =
        getImageFormatPngOutput("write_image_png_customChannel_rgb_float", "custom");
    verifyPng(customChannelPath, LodePNGColorType::LCT_RGB);
}

TEST_CASE("ImageFormatWriters/write_image_png_customChannel_rgb_int") {
    ImageFixture imageFixture;
    imageFixture.addCustomChannel(PixelFormat::UINT8, 3);
    const std::filesystem::path imagePath = getImageFormatPngOutput("write_image_png_customChannel_rgb_int");

    ImageFormatWriters::write(imagePath, imageFixture.image);

    verifyPng(imagePath, LodePNGColorType::LCT_RGB);
    const std::filesystem::path customChannelPath =
        getImageFormatPngOutput("write_image_png_customChannel_rgb_int", "custom");
    verifyPng(customChannelPath, LodePNGColorType::LCT_RGB);
}

TEST_CASE("ImageFormatWriters/write_image_png_customChannel_grey_float") {
    ImageFixture imageFixture;
    imageFixture.addCustomChannel(PixelFormat::FLOAT32, 1);
    const std::filesystem::path imagePath = getImageFormatPngOutput("write_image_png_customChannel_grey_float");

    ImageFormatWriters::write(imagePath, imageFixture.image);

    verifyPng(imagePath, LodePNGColorType::LCT_RGB);
    const std::filesystem::path customChannelPath =
        getImageFormatPngOutput("write_image_png_customChannel_grey_float", "custom");
    verifyPng(customChannelPath, LodePNGColorType::LCT_GREY);
}

TEST_CASE("ImageFormatWriters/write_image_png_customChannel_grey_int") {
    ImageFixture imageFixture;
    imageFixture.addCustomChannel(PixelFormat::UINT8, 1);
    const std::filesystem::path imagePath = getImageFormatPngOutput("write_image_png_customChannel_grey_int");

    ImageFormatWriters::write(imagePath, imageFixture.image);

    verifyPng(imagePath, LodePNGColorType::LCT_RGB);
    const std::filesystem::path customChannelPath =
        getImageFormatPngOutput("write_image_png_customChannel_grey_int", "custom");
    verifyPng(customChannelPath, LodePNGColorType::LCT_GREY);
}

TEST_CASE("ImageFormatWriters/write_image_empty_metadata") {
    ImageFixture imageFixture(false);
    const std::filesystem::path imagePath =
        getOutputFilename("ImageFormatWriters", "write_image_empty_metadata", ".png");

    ImageFormatWriters::write(imagePath, imageFixture.image);

    verifyPng(imagePath, LodePNGColorType::LCT_RGB, false);
}

TEST_CASE("ImageFormatWriters/write_film_png_rgb_float") {
    FilmFixture filmFixture;
    const std::filesystem::path imagePath = getImageFormatPngOutput("write_film_png_rgb_float");

    ImageFormatWriters::write(imagePath, filmFixture.film);

    verifyPng(imagePath, LodePNGColorType::LCT_RGB);
}

TEST_CASE("ImageFormatWriters/write_film_png_customChannel_rgb_float") {
    FilmFixture filmFixture;
    filmFixture.addCustomChannel(PixelFormat::FLOAT32, 3);
    const std::filesystem::path imagePath = getImageFormatPngOutput("write_film_png_customChannel_rgb_float");

    ImageFormatWriters::write(imagePath, filmFixture.film);

    verifyPng(imagePath, LodePNGColorType::LCT_RGB);
    const std::filesystem::path customChannelPath =
        getImageFormatPngOutput("write_film_png_customChannel_rgb_float", "custom");
    verifyPng(customChannelPath, LodePNGColorType::LCT_RGB);
}

TEST_CASE("ImageFormatWriters/write_film_png_customChannel_rgb_int") {
    FilmFixture filmFixture;
    filmFixture.addCustomChannel(PixelFormat::UINT8, 3);
    const std::filesystem::path imagePath = getImageFormatPngOutput("write_film_png_customChannel_rgb_int");

    ImageFormatWriters::write(imagePath, filmFixture.film);

    verifyPng(imagePath, LodePNGColorType::LCT_RGB);
    const std::filesystem::path customChannelPath =
        getImageFormatPngOutput("write_film_png_customChannel_rgb_int", "custom");
    verifyPng(customChannelPath, LodePNGColorType::LCT_RGB);
}

TEST_CASE("ImageFormatWriters/write_film_png_customChannel_grey_float") {
    FilmFixture filmFixture;
    filmFixture.addCustomChannel(PixelFormat::FLOAT32, 1);
    const std::filesystem::path imagePath = getImageFormatPngOutput("write_film_png_customChannel_grey_float");

    ImageFormatWriters::write(imagePath, filmFixture.film);

    verifyPng(imagePath, LodePNGColorType::LCT_RGB);
    const std::filesystem::path customChannelPath =
        getImageFormatPngOutput("write_film_png_customChannel_grey_float", "custom");
    verifyPng(customChannelPath, LodePNGColorType::LCT_GREY);
}

TEST_CASE("ImageFormatWriters/write_film_png_customChannel_grey_int") {
    FilmFixture filmFixture;
    filmFixture.addCustomChannel(PixelFormat::UINT8, 1);
    const std::filesystem::path imagePath = getImageFormatPngOutput("write_film_png_customChannel_grey_int");

    ImageFormatWriters::write(imagePath, filmFixture.film);

    verifyPng(imagePath, LodePNGColorType::LCT_RGB);
    const std::filesystem::path customChannelPath =
        getImageFormatPngOutput("write_film_png_customChannel_grey_int", "custom");
    verifyPng(customChannelPath, LodePNGColorType::LCT_GREY);
}

TEST_CASE("ImageFormatWriters/write_film_empty_metadata") {
    FilmFixture filmFixture(false);
    const std::filesystem::path imagePath =
        getOutputFilename("ImageFormatWriters", "write_film_empty_metadata", ".png");

    ImageFormatWriters::write(imagePath, filmFixture.film);

    verifyPng(imagePath, LodePNGColorType::LCT_RGB, false);
}

}