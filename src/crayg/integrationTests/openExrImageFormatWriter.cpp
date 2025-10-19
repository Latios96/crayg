#include "ImageAndFilmFixture.h"
#include "crayg/compatibility/openexr/fmt/ImathBox_formatter.h"
#include "crayg/compatibility/openexr/fmt/ImfPixelType_formatter.h"
#include "crayg/image/io/imageformatwriters/ImageFormatWriters.h"
#include "utils.h"
#include <ImathBox.h>
#include <ImfChannelList.h>
#include <ImfFloatAttribute.h>
#include <ImfHeader.h>
#include <ImfInputFile.h>
#include <ImfIntAttribute.h>
#include <ImfStringAttribute.h>
#include <catch2/catch.hpp>

namespace crayg {

std::string getImageFormatExrOutput(const std::string &testName) {
    return getOutputFilename("ImageFormatWriters", testName, ".exr");
}

CRAYG_DTO_2(ExrChannelSpec, std::string, name, Imf::PixelType, pixelType);

typedef std::vector<ExrChannelSpec> ChannelSpecVector;

void verifyExpectedChannels(Imf::Header &header, const ChannelSpecVector &expectedChannels) {
    ChannelSpecVector actualChannels;
    for (Imf::ChannelList::ConstIterator it = header.channels().begin(); it != header.channels().end(); ++it) {
        actualChannels.push_back({it.name(), it.channel().type});
    }

    REQUIRE(actualChannels == expectedChannels);
}

void verifyExpectedMetadataExists(const Imf::Header &header) {
    REQUIRE(dynamic_cast<const Imf::IntAttribute &>(header["test/int"]).value() == 42);
    REQUIRE(dynamic_cast<const Imf::FloatAttribute &>(header["test/float"]).value() == 42.42f);
    REQUIRE(dynamic_cast<const Imf::StringAttribute &>(header["test/string"]).value() == "teststring");
    REQUIRE(dynamic_cast<const Imf::IntAttribute &>(header["test/seconds"]).value() == 42);
}

void verifyCompressionIsCorrect(const Imf::Header &header, Imf::Compression compression) {
    REQUIRE(header.compression() == compression);
}

void verifyDisplayWindow(const Imf::Header &header) {
    REQUIRE(header.displayWindow() == Imath::Box2i({0, 0}, {127, 71}));
}

void verifyDataWindow(Imf::Header header, const Imath::Box2i &expectedDataWindow) {
    REQUIRE(header.dataWindow() == expectedDataWindow);
}

void verifyExr(const std::filesystem::path &path, const ChannelSpecVector &channels, Imf::Compression compression,
               const Imath::Box2i &dataWindow) {
    Imf::InputFile file(reinterpret_cast<const char *>(path.u8string().c_str()));
    Imf::Header header = file.header();

    verifyExpectedChannels(header, channels);
    verifyExpectedMetadataExists(header);
    verifyCompressionIsCorrect(header, compression);
    verifyDisplayWindow(header);
    verifyDataWindow(header, dataWindow);
}

void verifyExr(const std::filesystem::path &path, const ChannelSpecVector &channels) {
    verifyExr(path, channels, Imf::Compression::ZIP_COMPRESSION, Imath::Box2i({0, 0}, {127, 71}));
}

void verifyExr(const std::filesystem::path &path, const ChannelSpecVector &channels, Imf::Compression compression) {
    verifyExr(path, channels, compression, Imath::Box2i({0, 0}, {127, 71}));
}

void verifyExr(const std::filesystem::path &path, const ChannelSpecVector &channels, const Imath::Box2i &dataWindow) {
    verifyExr(path, channels, Imf::Compression::ZIP_COMPRESSION, dataWindow);
}

TEST_CASE("ImageFormatWriters/write_image_exr_rgb_with_different_compression") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    imageFormatWriteOptions.openExrFormatWriteOptions.compression = Imf::Compression::DWAA_COMPRESSION;
    ImageFixture imageFixture;
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_image_exr_rgb_with_different_compression");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::FLOAT}, {"g", Imf::FLOAT}, {"r", Imf::FLOAT}}),
              Imf::Compression::DWAA_COMPRESSION);
}

TEST_CASE("ImageFormatWriters/write_image_exr_rgb_floatAsFloat") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    ImageFixture imageFixture;
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_image_exr_rgb_floatAsFloat");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::FLOAT}, {"g", Imf::FLOAT}, {"r", Imf::FLOAT}}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_rgb_floatAsFloat_dataWindowAuto") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::AUTO;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    ImageFixture imageFixture(RENDER_REGION_BOUNDS, true, true);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_image_exr_rgb_floatAsFloat_dataWindowAuto");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::FLOAT}, {"g", Imf::FLOAT}, {"r", Imf::FLOAT}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_rgb_floatAsHalf") {
    ImageFixture imageFixture;
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_image_exr_rgb_floatAsHalf");

    ImageFormatWriters::write(imagePath, imageFixture.image);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::HALF}, {"g", Imf::HALF}, {"r", Imf::HALF}}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_rgb_floatAsHalf_dataWindowAuto") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::AUTO;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::HALF;
    ImageFixture imageFixture(RENDER_REGION_BOUNDS, true, true);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_image_exr_rgb_floatAsHalf_dataWindowAuto");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::HALF}, {"g", Imf::HALF}, {"r", Imf::HALF}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_customChannel_rgb_floatAsFloat") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    ImageFixture imageFixture;
    imageFixture.addCustomChannel(PixelFormat::FLOAT32, 3);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_image_exr_customChannel_rgb_floatAsFloat");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::FLOAT},
                                            {"custom.b", Imf::FLOAT},
                                            {"custom.g", Imf::FLOAT},
                                            {"custom.r", Imf::FLOAT},
                                            {"g", Imf::FLOAT},
                                            {"r", Imf::FLOAT}}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_customChannel_rgb_floatAsFloat_dataWindowAuto") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::AUTO;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    ImageFixture imageFixture(RENDER_REGION_BOUNDS, true, true);
    imageFixture.addCustomChannel(PixelFormat::FLOAT32, 3);
    const std::filesystem::path imagePath =
        getImageFormatExrOutput("write_image_exr_customChannel_rgb_floatAsFloat_dataWindowAuto");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::FLOAT},
                                 {"custom.b", Imf::FLOAT},
                                 {"custom.g", Imf::FLOAT},
                                 {"custom.r", Imf::FLOAT},
                                 {"g", Imf::FLOAT},
                                 {"r", Imf::FLOAT}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_customChannel_rgb_floatAsHalf") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::HALF;
    ImageFixture imageFixture;
    imageFixture.addCustomChannel(PixelFormat::FLOAT32, 3);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_image_exr_customChannel_rgb_floatAsHalf");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::HALF},
                                            {"custom.b", Imf::HALF},
                                            {"custom.g", Imf::HALF},
                                            {"custom.r", Imf::HALF},
                                            {"g", Imf::HALF},
                                            {"r", Imf::HALF}}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_customChannel_rgb_floatAsHalf_dataWindowAuto") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::AUTO;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::HALF;
    ImageFixture imageFixture(RENDER_REGION_BOUNDS, true, true);
    imageFixture.addCustomChannel(PixelFormat::FLOAT32, 3);
    const std::filesystem::path imagePath =
        getImageFormatExrOutput("write_image_exr_customChannel_rgb_floatAsHalf_dataWindowAuto");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::HALF},
                                 {"custom.b", Imf::HALF},
                                 {"custom.g", Imf::HALF},
                                 {"custom.r", Imf::HALF},
                                 {"g", Imf::HALF},
                                 {"r", Imf::HALF}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_customChannel_rgb_intAsFloat") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    ImageFixture imageFixture;
    imageFixture.addCustomChannel(PixelFormat::UINT8, 3);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_image_exr_customChannel_rgb_intAsFloat");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::FLOAT},
                                            {"custom.b", Imf::FLOAT},
                                            {"custom.g", Imf::FLOAT},
                                            {"custom.r", Imf::FLOAT},
                                            {"g", Imf::FLOAT},
                                            {"r", Imf::FLOAT}}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_customChannel_rgb_intAsFloat_dataWindowAuto") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::AUTO;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    ImageFixture imageFixture(RENDER_REGION_BOUNDS, true, true);
    imageFixture.addCustomChannel(PixelFormat::UINT8, 3);
    const std::filesystem::path imagePath =
        getImageFormatExrOutput("write_image_exr_customChannel_rgb_intAsFloat_dataWindowAuto");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::FLOAT},
                                 {"custom.b", Imf::FLOAT},
                                 {"custom.g", Imf::FLOAT},
                                 {"custom.r", Imf::FLOAT},
                                 {"g", Imf::FLOAT},
                                 {"r", Imf::FLOAT}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_customChannel_rgb_intAsHalf") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::HALF;
    ImageFixture imageFixture;
    imageFixture.addCustomChannel(PixelFormat::UINT8, 3);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_image_exr_customChannel_rgb_intAsHalf");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::HALF},
                                            {"custom.b", Imf::HALF},
                                            {"custom.g", Imf::HALF},
                                            {"custom.r", Imf::HALF},
                                            {"g", Imf::HALF},
                                            {"r", Imf::HALF}}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_customChannel_rgb_intAsHalf_dataWindowAuto") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::AUTO;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::HALF;
    ImageFixture imageFixture(RENDER_REGION_BOUNDS, true, true);
    imageFixture.addCustomChannel(PixelFormat::UINT8, 3);
    const std::filesystem::path imagePath =
        getImageFormatExrOutput("write_image_exr_customChannel_rgb_intAsHalf_dataWindowAuto");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::HALF},
                                 {"custom.b", Imf::HALF},
                                 {"custom.g", Imf::HALF},
                                 {"custom.r", Imf::HALF},
                                 {"g", Imf::HALF},
                                 {"r", Imf::HALF}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_customChannel_grey_floatAsFloat") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    ImageFixture imageFixture;
    imageFixture.addCustomChannel(PixelFormat::FLOAT32, 1);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_image_exr_customChannel_grey_floatAsFloat");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::FLOAT}, {"custom", Imf::FLOAT}, {"g", Imf::FLOAT}, {"r", Imf::FLOAT}}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_customChannel_grey_floatAsFloat_dataWindowAuto") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::AUTO;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    ImageFixture imageFixture(RENDER_REGION_BOUNDS, true, true);
    imageFixture.addCustomChannel(PixelFormat::FLOAT32, 1);
    const std::filesystem::path imagePath =
        getImageFormatExrOutput("write_image_exr_customChannel_grey_floatAsFloat_dataWindowAuto");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::FLOAT}, {"custom", Imf::FLOAT}, {"g", Imf::FLOAT}, {"r", Imf::FLOAT}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_customChannel_grey_floatAsHalf") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::HALF;
    ImageFixture imageFixture;
    imageFixture.addCustomChannel(PixelFormat::FLOAT32, 1);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_image_exr_customChannel_grey_floatAsHalf");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::HALF}, {"custom", Imf::HALF}, {"g", Imf::HALF}, {"r", Imf::HALF}}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_customChannel_grey_floatAsHalf_dataWindowAuto") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::AUTO;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::HALF;
    ImageFixture imageFixture(RENDER_REGION_BOUNDS, true, true);
    imageFixture.addCustomChannel(PixelFormat::FLOAT32, 1);
    const std::filesystem::path imagePath =
        getImageFormatExrOutput("write_image_exr_customChannel_grey_floatAsHalf_dataWindowAuto");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::HALF}, {"custom", Imf::HALF}, {"g", Imf::HALF}, {"r", Imf::HALF}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_customChannel_grey_intAsFloat") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    ImageFixture imageFixture;
    imageFixture.addCustomChannel(PixelFormat::UINT8, 1);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_image_exr_customChannel_grey_intAsFloat");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::FLOAT}, {"custom", Imf::FLOAT}, {"g", Imf::FLOAT}, {"r", Imf::FLOAT}}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_customChannel_grey_intAsFloat_dataWindowAuto") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::AUTO;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    ImageFixture imageFixture(RENDER_REGION_BOUNDS, true, true);
    imageFixture.addCustomChannel(PixelFormat::UINT8, 1);
    const std::filesystem::path imagePath =
        getImageFormatExrOutput("write_image_exr_customChannel_grey_intAsFloat_dataWindowAuto");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::FLOAT}, {"custom", Imf::FLOAT}, {"g", Imf::FLOAT}, {"r", Imf::FLOAT}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_customChannel_grey_intAsHalf") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::HALF;
    ImageFixture imageFixture;
    imageFixture.addCustomChannel(PixelFormat::UINT8, 1);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_image_exr_customChannel_grey_intAsHalf");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::HALF}, {"custom", Imf::HALF}, {"g", Imf::HALF}, {"r", Imf::HALF}}));
}

TEST_CASE("ImageFormatWriters/write_image_exr_customChannel_grey_intAsHalf_dataWindowAuto") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::AUTO;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::HALF;
    ImageFixture imageFixture(RENDER_REGION_BOUNDS, true, true);
    imageFixture.addCustomChannel(PixelFormat::UINT8, 1);
    const std::filesystem::path imagePath =
        getImageFormatExrOutput("write_image_exr_customChannel_grey_intAsHalf_dataWindowAuto");

    ImageFormatWriters::write(imagePath, imageFixture.image, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::HALF}, {"custom", Imf::HALF}, {"g", Imf::HALF}, {"r", Imf::HALF}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_rgb_with_different_compression") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    imageFormatWriteOptions.openExrFormatWriteOptions.compression = Imf::Compression::DWAA_COMPRESSION;
    FilmFixture filmFixture;
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_film_exr_rgb_with_different_compression");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::FLOAT}, {"g", Imf::FLOAT}, {"r", Imf::FLOAT}}),
              Imf::Compression::DWAA_COMPRESSION);
}

TEST_CASE("ImageFormatWriters/write_film_exr_rgb_floatAsFloat") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    FilmFixture filmFixture;
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_film_exr_rgb_floatAsFloat");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::FLOAT}, {"g", Imf::FLOAT}, {"r", Imf::FLOAT}}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_rgb_floatAsFloat_dataWindowRenderRegion") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::RENDER_REGION;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    FilmFixture filmFixture(RENDER_REGION_BOUNDS, true, true);
    const std::filesystem::path imagePath =
        getImageFormatExrOutput("write_film_exr_rgb_floatAsFloat_dataWindowRenderRegion");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::FLOAT}, {"g", Imf::FLOAT}, {"r", Imf::FLOAT}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_rgb_floatAsHalf") {
    FilmFixture filmFixture;
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_film_exr_rgb_floatAsHalf");

    ImageFormatWriters::write(imagePath, filmFixture.film);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::HALF}, {"g", Imf::HALF}, {"r", Imf::HALF}}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_rgb_floatAsHalf_dataWindowRenderRegion") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::RENDER_REGION;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::HALF;
    FilmFixture filmFixture(RENDER_REGION_BOUNDS, true, true);
    const std::filesystem::path imagePath =
        getImageFormatExrOutput("write_film_exr_rgb_floatAsHalf_dataWindowRenderRegion");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::HALF}, {"g", Imf::HALF}, {"r", Imf::HALF}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_customChannel_rgb_floatAsFloat") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    FilmFixture filmFixture;
    filmFixture.addCustomChannel(PixelFormat::FLOAT32, 3);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_film_exr_customChannel_rgb_floatAsFloat");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::FLOAT},
                                            {"custom.b", Imf::FLOAT},
                                            {"custom.g", Imf::FLOAT},
                                            {"custom.r", Imf::FLOAT},
                                            {"g", Imf::FLOAT},
                                            {"r", Imf::FLOAT}}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_customChannel_rgb_floatAsFloat_dataWindowRenderRegion") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::RENDER_REGION;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    FilmFixture filmFixture(RENDER_REGION_BOUNDS, true, true);
    filmFixture.addCustomChannel(PixelFormat::FLOAT32, 3);
    const std::filesystem::path imagePath =
        getImageFormatExrOutput("write_film_exr_customChannel_rgb_floatAsFloat_dataWindowRenderRegion");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::FLOAT},
                                 {"custom.b", Imf::FLOAT},
                                 {"custom.g", Imf::FLOAT},
                                 {"custom.r", Imf::FLOAT},
                                 {"g", Imf::FLOAT},
                                 {"r", Imf::FLOAT}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_customChannel_rgb_floatAsHalf") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::HALF;
    FilmFixture filmFixture;
    filmFixture.addCustomChannel(PixelFormat::FLOAT32, 3);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_film_exr_customChannel_rgb_floatAsHalf");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::HALF},
                                            {"custom.b", Imf::HALF},
                                            {"custom.g", Imf::HALF},
                                            {"custom.r", Imf::HALF},
                                            {"g", Imf::HALF},
                                            {"r", Imf::HALF}}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_customChannel_rgb_floatAsHalf_dataWindowRenderRegion") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::RENDER_REGION;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::HALF;
    FilmFixture filmFixture(RENDER_REGION_BOUNDS, true, true);
    filmFixture.addCustomChannel(PixelFormat::FLOAT32, 3);
    const std::filesystem::path imagePath =
        getImageFormatExrOutput("write_film_exr_customChannel_rgb_floatAsHalf_dataWindowRenderRegion");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::HALF},
                                 {"custom.b", Imf::HALF},
                                 {"custom.g", Imf::HALF},
                                 {"custom.r", Imf::HALF},
                                 {"g", Imf::HALF},
                                 {"r", Imf::HALF}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_customChannel_rgb_intAsFloat") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    FilmFixture filmFixture;
    filmFixture.addCustomChannel(PixelFormat::UINT8, 3);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_film_exr_customChannel_rgb_intAsFloat");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::FLOAT},
                                            {"custom.b", Imf::FLOAT},
                                            {"custom.g", Imf::FLOAT},
                                            {"custom.r", Imf::FLOAT},
                                            {"g", Imf::FLOAT},
                                            {"r", Imf::FLOAT}}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_customChannel_rgb_intAsFloat_dataWindowRenderRegion") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::RENDER_REGION;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    FilmFixture filmFixture(RENDER_REGION_BOUNDS, true, true);
    filmFixture.addCustomChannel(PixelFormat::UINT8, 3);
    const std::filesystem::path imagePath =
        getImageFormatExrOutput("write_film_exr_customChannel_rgb_intAsFloat_dataWindowRenderRegion");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::FLOAT},
                                 {"custom.b", Imf::FLOAT},
                                 {"custom.g", Imf::FLOAT},
                                 {"custom.r", Imf::FLOAT},
                                 {"g", Imf::FLOAT},
                                 {"r", Imf::FLOAT}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_customChannel_rgb_intAsHalf") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::HALF;
    FilmFixture filmFixture;
    filmFixture.addCustomChannel(PixelFormat::UINT8, 3);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_film_exr_customChannel_rgb_intAsHalf");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::HALF},
                                            {"custom.b", Imf::HALF},
                                            {"custom.g", Imf::HALF},
                                            {"custom.r", Imf::HALF},
                                            {"g", Imf::HALF},
                                            {"r", Imf::HALF}}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_customChannel_rgb_intAsHalf_dataWindowRenderRegion") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::RENDER_REGION;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::HALF;
    FilmFixture filmFixture(RENDER_REGION_BOUNDS, true, true);
    filmFixture.addCustomChannel(PixelFormat::UINT8, 3);
    const std::filesystem::path imagePath =
        getImageFormatExrOutput("write_film_exr_customChannel_rgb_intAsHalf_dataWindowRenderRegion");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::HALF},
                                 {"custom.b", Imf::HALF},
                                 {"custom.g", Imf::HALF},
                                 {"custom.r", Imf::HALF},
                                 {"g", Imf::HALF},
                                 {"r", Imf::HALF}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_customChannel_grey_floatAsFloat") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    FilmFixture filmFixture;
    filmFixture.addCustomChannel(PixelFormat::FLOAT32, 1);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_film_exr_customChannel_grey_floatAsFloat");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::FLOAT}, {"custom", Imf::FLOAT}, {"g", Imf::FLOAT}, {"r", Imf::FLOAT}}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_customChannel_grey_floatAsFloat_dataWindowRenderRegion") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::RENDER_REGION;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    FilmFixture filmFixture(RENDER_REGION_BOUNDS, true, true);
    filmFixture.addCustomChannel(PixelFormat::FLOAT32, 1);
    const std::filesystem::path imagePath =
        getImageFormatExrOutput("write_film_exr_customChannel_grey_floatAsFloat_dataWindowRenderRegion");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::FLOAT}, {"custom", Imf::FLOAT}, {"g", Imf::FLOAT}, {"r", Imf::FLOAT}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_customChannel_grey_floatAsHalf") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::HALF;
    FilmFixture filmFixture;
    filmFixture.addCustomChannel(PixelFormat::FLOAT32, 1);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_film_exr_customChannel_grey_floatAsHalf");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::HALF}, {"custom", Imf::HALF}, {"g", Imf::HALF}, {"r", Imf::HALF}}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_customChannel_grey_floatAsHalf_dataWindowRenderRegion") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::RENDER_REGION;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::HALF;
    FilmFixture filmFixture(RENDER_REGION_BOUNDS, true, true);
    filmFixture.addCustomChannel(PixelFormat::FLOAT32, 1);
    const std::filesystem::path imagePath =
        getImageFormatExrOutput("write_film_exr_customChannel_grey_floatAsHalf_dataWindowRenderRegion");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::HALF}, {"custom", Imf::HALF}, {"g", Imf::HALF}, {"r", Imf::HALF}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_customChannel_grey_intAsFloat") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    FilmFixture filmFixture;
    filmFixture.addCustomChannel(PixelFormat::UINT8, 1);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_film_exr_customChannel_grey_intAsFloat");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::FLOAT}, {"custom", Imf::FLOAT}, {"g", Imf::FLOAT}, {"r", Imf::FLOAT}}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_customChannel_grey_intAsFloat_dataWindowRenderRegion") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::RENDER_REGION;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    FilmFixture filmFixture(RENDER_REGION_BOUNDS, true, true);
    filmFixture.addCustomChannel(PixelFormat::UINT8, 1);
    const std::filesystem::path imagePath =
        getImageFormatExrOutput("write_film_exr_customChannel_grey_intAsFloat_dataWindowRenderRegion");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::FLOAT}, {"custom", Imf::FLOAT}, {"g", Imf::FLOAT}, {"r", Imf::FLOAT}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_customChannel_grey_intAsHalf") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::HALF;
    FilmFixture filmFixture;
    filmFixture.addCustomChannel(PixelFormat::UINT8, 1);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_film_exr_customChannel_grey_intAsHalf");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::HALF}, {"custom", Imf::HALF}, {"g", Imf::HALF}, {"r", Imf::HALF}}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_customChannel_grey_intAsHalf_dataWindowRenderRegion") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::RENDER_REGION;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::HALF;
    FilmFixture filmFixture(RENDER_REGION_BOUNDS, true, true);
    filmFixture.addCustomChannel(PixelFormat::UINT8, 1);
    const std::filesystem::path imagePath =
        getImageFormatExrOutput("write_film_exr_customChannel_grey_intAsHalf_dataWindowRenderRegion");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath,
              ChannelSpecVector({{"b", Imf::HALF}, {"custom", Imf::HALF}, {"g", Imf::HALF}, {"r", Imf::HALF}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

TEST_CASE("ImageFormatWriters/write_film_exr_dataWindowAuto") {
    ImageFormatWriteOptions imageFormatWriteOptions{};
    imageFormatWriteOptions.openExrFormatWriteOptions.openExrDataWindow = OpenExrDataWindow::AUTO;
    imageFormatWriteOptions.openExrFormatWriteOptions.pixelType = Imf::PixelType::FLOAT;
    FilmFixture filmFixture(RENDER_REGION_BOUNDS, true, true);
    const std::filesystem::path imagePath = getImageFormatExrOutput("write_film_exr_dataWindowAuto");

    ImageFormatWriters::write(imagePath, filmFixture.film, imageFormatWriteOptions);

    verifyExr(imagePath, ChannelSpecVector({{"b", Imf::FLOAT}, {"g", Imf::FLOAT}, {"r", Imf::FLOAT}}),
              Imath::Box2i({9, 9}, {127 - 9, 71 - 9}));
}

}
