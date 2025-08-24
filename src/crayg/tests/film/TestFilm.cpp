#include "image/Image.h"
#include "image/film/Film.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("Film::construct") {

    SECTION("should construct correctly from dimensions") {
        Film film(10, 5);

        REQUIRE(film.getFilmSpec() == FilmSpec(Resolution(10, 5),
                                               std::vector<FilmBufferSpec>(
                                                   {{"color", FilmBufferType::ACCUMULATION, PixelFormat::FLOAT32, 3}}),
                                               std::nullopt));
    }

    SECTION("should construct correctly from dimensions") {
        Film film(Resolution(10, 5));

        REQUIRE(film.getFilmSpec() == FilmSpec(Resolution(10, 5),
                                               std::vector<FilmBufferSpec>(
                                                   {{"color", FilmBufferType::ACCUMULATION, PixelFormat::FLOAT32, 3}}),
                                               std::nullopt));
    }

    SECTION("should construct from FilmSpec") {
        Film film(FilmSpecBuilder(Resolution(10, 5), FilmBufferType::SUM, PixelFormat::FLOAT32).finish());

        REQUIRE(film.getFilmSpec() ==
                FilmSpec(Resolution(10, 5),
                         std::vector<FilmBufferSpec>({{"color", FilmBufferType::SUM, PixelFormat::FLOAT32, 3}}),
                         std::nullopt));
    }
}

TEST_CASE("Film::channelNames()") {

    SECTION("should return only color") {
        Film film(10, 5);

        REQUIRE(film.channelNames() == std::vector<std::string>({"color"}));
    }
    SECTION("should return all names") {
        auto buffer = new FloatValueBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("test", buffer);

        REQUIRE(film.channelNames() == std::vector<std::string>({"color", "test"}));
    }
}

TEST_CASE("Film::addChannel()") {
    Film film(10, 5);
    SECTION("should add channel") {
        auto buffer = new FloatValueBuffer(10, 5);

        film.addChannel("test", buffer);

        REQUIRE(film.channelNames() == std::vector<std::string>({"color", "test"}));
    }

    SECTION("should not add color") {
        film.addSample("color", {0, 0}, 1);
        auto buffer = new FloatValueBuffer(10, 5);

        film.addChannel("color", buffer);

        REQUIRE(film.channelNames() == std::vector<std::string>({"color"}));
        auto bufferVariant = film.getBufferVariantPtrByName("color");
        REQUIRE_FALSE(std::get<Color3fAccumulationBuffer *>(*bufferVariant)->sumIsZero());
    }

    SECTION("should throw if resolutions don't match") {

        auto buffer = new FloatValueBuffer(5, 5);

        REQUIRE_THROWS(film.addChannel("test", buffer));
    }

    SECTION("should keep when adding channel with same name") {
        auto buffer = new FloatValueBuffer(10, 5);
        film.addChannel("test", buffer);
        film.addSample("test", {0, 0}, 1);
        film.addChannel("test", buffer);

        REQUIRE(film.channelNames() == std::vector<std::string>({"color", "test"}));
        auto bufferVariant = film.getBufferVariantPtrByName("test");
        REQUIRE_FALSE(std::get<FloatValueBuffer *>(*bufferVariant)->isBlack());
    }
}

TEST_CASE("Film::hasChannel()") {

    SECTION("should return true for color") {
        Film film(10, 5);

        REQUIRE(film.hasChannel("color"));
    }

    SECTION("should return true for existing custom channel") {
        auto buffer = new FloatValueBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("test", buffer);

        REQUIRE(film.hasChannel("test"));
    }

    SECTION("should return false for not-existing custom channel") {
        Film film(10, 5);

        REQUIRE_FALSE(film.hasChannel("test"));
    }
}

TEST_CASE("Film::getChannels()") {

    SECTION("should return only color channel") {
        Film film(10, 5);

        const auto channels = film.getChannels();

        REQUIRE(channels.size() == 1);
        REQUIRE(channels[0].channelName == "color");
        REQUIRE(std::holds_alternative<Color3fAccumulationBuffer *>(channels[0].channelBuffer));
    }

    SECTION("should return custom channel") {
        auto buffer = new FloatValueBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("test", buffer);

        const auto channels = film.getChannels();

        REQUIRE(channels.size() == 2);
        REQUIRE(channels[0].channelName == "color");
        REQUIRE(std::holds_alternative<Color3fAccumulationBuffer *>(channels[0].channelBuffer));
        REQUIRE(channels[1].channelName == "test");
        REQUIRE(std::holds_alternative<FloatValueBuffer *>(channels[1].channelBuffer));
    }
}

TEST_CASE("Film::getBufferVariantPtrByName()") {

    SECTION("should return color channel") {
        Film film(10, 5);

        auto bufferVariant = film.getBufferVariantPtrByName("color");

        REQUIRE(bufferVariant.has_value());
        REQUIRE(std::holds_alternative<Color3fAccumulationBuffer *>(*bufferVariant));
    }

    SECTION("should return empty for non-existing custom channel") {
        Film film(10, 5);

        auto bufferVariant = film.getBufferVariantPtrByName("test");

        REQUIRE_FALSE(bufferVariant.has_value());
    }

    SECTION("should return color channel") {
        auto buffer = new FloatValueBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("test", buffer);

        auto bufferVariant = film.getBufferVariantPtrByName("test");

        REQUIRE(bufferVariant.has_value());
        REQUIRE(std::holds_alternative<FloatValueBuffer *>(*bufferVariant));
    }
}

TEST_CASE("Film::addSample()") {

    SECTION("should add Color sample to color") {
        Film film(10, 5);

        film.addSample("color", {0, 0}, Color(1, 2, 3));

        auto bufferVariant = film.getBufferVariantPtrByName("color");
        REQUIRE(bufferVariant.has_value());
        REQUIRE_FALSE(std::get<Color3fAccumulationBuffer *>(*bufferVariant)->sumIsZero());
    }

    SECTION("should add float sample to color") {
        Film film(10, 5);

        film.addSample("color", {0, 0}, 1);

        auto bufferVariant = film.getBufferVariantPtrByName("color");
        REQUIRE(bufferVariant.has_value());
        REQUIRE_FALSE(std::get<Color3fAccumulationBuffer *>(*bufferVariant)->sumIsZero());
    }

    SECTION("should not crash when adding color sample to not existing channel") {
        Film film(10, 5);

        film.addSample("test", {0, 0}, Color(1, 2, 3));
    }

    SECTION("should add float sample to color") {
        Film film(10, 5);

        film.addSample("test", {0, 0}, 1);
    }

    SECTION("should add color sample to custom accumulation buffer channel") {
        auto buffer = new Color3fAccumulationBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("test", buffer);

        film.addSample("test", {0, 0}, Color(1, 2, 3));

        auto bufferVariant = film.getBufferVariantPtrByName("test");
        REQUIRE(bufferVariant.has_value());
        REQUIRE_FALSE(std::get<Color3fAccumulationBuffer *>(*bufferVariant)->sumIsZero());
    }

    SECTION("should add float sample to custom accumulation buffer channel") {
        auto buffer = new Color3fAccumulationBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("test", buffer);

        film.addSample("test", {0, 0}, 1);

        auto bufferVariant = film.getBufferVariantPtrByName("test");
        REQUIRE(bufferVariant.has_value());
        REQUIRE_FALSE(std::get<Color3fAccumulationBuffer *>(*bufferVariant)->sumIsZero());
    }

    SECTION("should add color sample to custom value buffer channel") {
        auto buffer = new Color3fValueBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("test", buffer);

        film.addSample("test", {0, 0}, Color(1, 2, 3));

        auto bufferVariant = film.getBufferVariantPtrByName("test");
        REQUIRE(bufferVariant.has_value());
        REQUIRE_FALSE(std::get<Color3fValueBuffer *>(*bufferVariant)->isBlack());
    }

    SECTION("should add float sample to custom value buffer channel") {
        auto buffer = new Color3fValueBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("test", buffer);

        film.addSample("test", {0, 0}, 1);

        auto bufferVariant = film.getBufferVariantPtrByName("test");
        REQUIRE(bufferVariant.has_value());
        REQUIRE_FALSE(std::get<Color3fValueBuffer *>(*bufferVariant)->isBlack());
    }

    SECTION("should add color sample to custom sum buffer channel") {
        auto buffer = new Color3fSumBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("test", buffer);

        film.addSample("test", {0, 0}, Color(1, 2, 3));

        auto bufferVariant = film.getBufferVariantPtrByName("test");
        REQUIRE(bufferVariant.has_value());
        REQUIRE_FALSE(std::get<Color3fSumBuffer *>(*bufferVariant)->isBlack());
    }

    SECTION("should add float sample to custom sum buffer channel") {
        auto buffer = new Color3fSumBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("test", buffer);

        film.addSample("test", {0, 0}, 1);

        auto bufferVariant = film.getBufferVariantPtrByName("test");
        REQUIRE(bufferVariant.has_value());
        REQUIRE_FALSE(std::get<Color3fSumBuffer *>(*bufferVariant)->isBlack());
    }
}

TEST_CASE("Film::updateAverages()") {

    SECTION("should update color channel") {
        Film film(10, 5);
        film.addSample("color", {0, 0}, Color(1, 2, 3));
        auto bufferVariant = film.getBufferVariantPtrByName("color");
        REQUIRE(std::get<Color3fAccumulationBuffer *>(*bufferVariant)->isBlack());

        film.updateAverages();

        REQUIRE_FALSE(std::get<Color3fAccumulationBuffer *>(*bufferVariant)->isBlack());
    }

    SECTION("should update custom accumulation buffer") {
        auto custom = new Color3fAccumulationBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("test", custom);
        film.addSample("test", {0, 0}, Color(1, 2, 3));
        REQUIRE(custom->isBlack());

        film.updateAverages();

        REQUIRE_FALSE(custom->isBlack());
    }

    SECTION("should not update custom non-accumulation buffer") {
        auto customValueBuffer = new Color3fValueBuffer(10, 5);
        auto customAccumulationBuffer = new Color3fAccumulationBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("accumulation", customAccumulationBuffer);
        film.addChannel("value", customValueBuffer);
        film.addSample("accumulation", {0, 0}, Color(1, 2, 3));
        REQUIRE(customAccumulationBuffer->isBlack());
        REQUIRE(customValueBuffer->isBlack());

        film.updateAverages();

        REQUIRE_FALSE(customAccumulationBuffer->isBlack());
        REQUIRE(customValueBuffer->isBlack());
    }
}

TEST_CASE("Film::updateAveragesForChannel()") {

    SECTION("should update only accumulation buffer") {
        auto custom = new Color3fAccumulationBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("test", custom);
        film.addSample("color", {0, 0}, Color(1, 2, 3));
        film.addSample("test", {0, 0}, Color(1, 2, 3));
        REQUIRE(custom->isBlack());

        film.updateAveragesForChannel("test");

        auto bufferVariant = film.getBufferVariantPtrByName("color");
        REQUIRE(std::get<Color3fAccumulationBuffer *>(*bufferVariant)->isBlack());
        REQUIRE_FALSE(custom->isBlack());
    }

    SECTION("should not update custom non-accumulation buffer") {
        auto customValueBuffer = new Color3fValueBuffer(10, 5);
        auto customAccumulationBuffer = new Color3fAccumulationBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("accumulation", customAccumulationBuffer);
        film.addChannel("value", customValueBuffer);
        film.addSample("accumulation", {0, 0}, Color(1, 2, 3));
        REQUIRE(customAccumulationBuffer->isBlack());
        REQUIRE(customValueBuffer->isBlack());

        film.updateAveragesForChannel("accumulation");

        REQUIRE_FALSE(customAccumulationBuffer->isBlack());
        REQUIRE(customValueBuffer->isBlack());
    }
}

TEST_CASE("Film::updateAveragesInTile()") {

    SECTION("should update color channel") {
        Film film(10, 5);
        film.addSample("color", {0, 0}, Color(1, 2, 3));
        film.addSample("color", {4, 4}, Color(1, 2, 3));
        auto bufferVariant = film.getBufferVariantPtrByName("color");
        REQUIRE(std::get<Color3fAccumulationBuffer *>(*bufferVariant)->isBlack());

        film.updateAveragesInTile(Tile({0, 0}, 3, 3));

        REQUIRE(std::get<Color3fAccumulationBuffer *>(*bufferVariant)->getColor({0, 0}) == Color(1, 2, 3));
        REQUIRE(std::get<Color3fAccumulationBuffer *>(*bufferVariant)->getColor({4, 4}).isBlack());
    }

    SECTION("should update custom accumulation buffer") {
        auto custom = new Color3fAccumulationBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("test", custom);
        film.addSample("test", {0, 0}, Color(1, 2, 3));
        film.addSample("test", {4, 4}, Color(1, 2, 3));
        REQUIRE(custom->isBlack());

        film.updateAveragesInTile(Tile({0, 0}, 3, 3));

        REQUIRE(custom->getColor({0, 0}) == Color(1, 2, 3));
        REQUIRE(custom->getColor({4, 4}).isBlack());
    }

    SECTION("should not update custom non-accumulation buffer") {
        auto customValueBuffer = new Color3fValueBuffer(10, 5);
        auto customAccumulationBuffer = new Color3fAccumulationBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("accumulation", customAccumulationBuffer);
        film.addChannel("value", customValueBuffer);
        film.addSample("accumulation", {0, 0}, Color(1, 2, 3));
        film.addSample("accumulation", {4, 4}, Color(1, 2, 3));
        REQUIRE(customAccumulationBuffer->isBlack());
        REQUIRE(customValueBuffer->isBlack());

        film.updateAveragesInTile(Tile({0, 0}, 3, 3));

        REQUIRE(customAccumulationBuffer->getColor({0, 0}) == Color(1, 2, 3));
        REQUIRE(customAccumulationBuffer->getColor({4, 4}) == Color(0, 0, 0));
        REQUIRE(customValueBuffer->isBlack());
    }
}

TEST_CASE("Film::updateAveragesForChannelInTile()") {

    SECTION("should update color channel") {
        Film film(10, 5);
        film.addSample("color", {0, 0}, Color(1, 2, 3));
        film.addSample("color", {4, 4}, Color(1, 2, 3));
        auto bufferVariant = film.getBufferVariantPtrByName("color");
        REQUIRE(std::get<Color3fAccumulationBuffer *>(*bufferVariant)->isBlack());

        film.updateAveragesForChannelInTile(Tile({0, 0}, 3, 3), "color");

        REQUIRE(std::get<Color3fAccumulationBuffer *>(*bufferVariant)->getColor({0, 0}) == Color(1, 2, 3));
        REQUIRE(std::get<Color3fAccumulationBuffer *>(*bufferVariant)->getColor({4, 4}).isBlack());
    }

    SECTION("should update custom accumulation buffer") {
        auto custom = new Color3fAccumulationBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("test", custom);
        film.addSample("color", {0, 0}, Color(1, 2, 3));
        film.addSample("test", {0, 0}, Color(1, 2, 3));
        film.addSample("test", {4, 4}, Color(1, 2, 3));
        REQUIRE(custom->isBlack());

        film.updateAveragesForChannelInTile(Tile({0, 0}, 3, 3), "test");

        REQUIRE(custom->getColor({0, 0}) == Color(1, 2, 3));
        REQUIRE(custom->getColor({4, 4}).isBlack());
        auto bufferVariant = film.getBufferVariantPtrByName("test");
        REQUIRE_FALSE(std::get<Color3fAccumulationBuffer *>(*bufferVariant)->isBlack());
    }

    SECTION("should not update custom non-accumulation buffer") {
        auto customValueBuffer = new Color3fValueBuffer(10, 5);
        auto customAccumulationBuffer = new Color3fAccumulationBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("accumulation", customAccumulationBuffer);
        film.addChannel("value", customValueBuffer);
        film.addSample("accumulation", {0, 0}, Color(1, 2, 3));
        film.addSample("accumulation", {4, 4}, Color(1, 2, 3));
        REQUIRE(customAccumulationBuffer->isBlack());
        REQUIRE(customValueBuffer->isBlack());

        film.updateAveragesForChannelInTile(Tile({0, 0}, 3, 3), "accumulation");

        REQUIRE(customAccumulationBuffer->getColor({0, 0}) == Color(1, 2, 3));
        REQUIRE(customAccumulationBuffer->getColor({4, 4}) == Color(0, 0, 0));
        REQUIRE(customValueBuffer->isBlack());
    }
}

TEST_CASE("Film::addChannelsFromSpec") {

    SECTION("should throw if resolutions do not match") {
        Film film(10, 20);
        FilmSpec filmSpec({1, 1}, {{"color", FilmBufferType::ACCUMULATION, PixelFormat::FLOAT32, 3}}, std::nullopt);

        REQUIRE_THROWS_AS(film.addChannelsFromSpec(filmSpec), std::runtime_error);
    }

    SECTION("should add channels from spec") {
        Film film(10, 20);
        FilmSpec filmSpec({10, 20},
                          {{"color", FilmBufferType::ACCUMULATION, PixelFormat::FLOAT32, 3},
                           {"alpha", FilmBufferType::VALUE, PixelFormat::FLOAT32, 1},
                           {"depth", FilmBufferType::VALUE, PixelFormat::FLOAT32, 1}},
                          std::nullopt);

        film.addChannelsFromSpec(filmSpec);

        REQUIRE(film.channelNames() == std::vector<std::string>({"color", "alpha", "depth"}));
        REQUIRE(std::holds_alternative<FloatValueBuffer *>(*film.getBufferVariantPtrByName("alpha")));
        REQUIRE(std::holds_alternative<FloatValueBuffer *>(*film.getBufferVariantPtrByName("depth")));
    }
}

TEST_CASE("Film::toImage") {

    SECTION("should convert color only image") {
        Film film(10, 5);
        film.addSample("color", {3, 3}, Color(1, 2, 3));
        film.updateAverages();

        Image image(10, 5);
        film.toImage(image);

        REQUIRE(image.channelNames() == std::vector<std::string>({"rgb"}));
        REQUIRE_FALSE(image.rgb.isBlack());
        REQUIRE(image.rgb.getPixelFormat() == PixelFormat::FLOAT32);
        REQUIRE(image.rgb.getColorChannelCount() == 3);
    }

    SECTION("should convert custom float channel") {
        auto customValueBuffer = new FloatValueBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("test", customValueBuffer);

        film.addSample("color", {3, 3}, Color(1, 2, 3));
        film.addSample("test", {3, 3}, Color(1, 2, 3));
        film.updateAverages();

        Image image(10, 5);
        film.toImage(image);

        REQUIRE(image.channelNames() == std::vector<std::string>({"rgb", "test"}));
        REQUIRE_FALSE(image.rgb.isBlack());
        auto testChannel = image.getChannel("test");
        REQUIRE_FALSE(testChannel->isBlack());
        REQUIRE(testChannel->getPixelFormat() == PixelFormat::FLOAT32);
        REQUIRE(testChannel->getColorChannelCount() == 1);
    }

    SECTION("should convert custom int channel") {
        auto customValueBuffer = new IntValueBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("test", customValueBuffer);

        film.addSample("color", {3, 3}, Color(1, 2, 3));
        film.addSample("test", {3, 3}, Color(1, 2, 3));
        film.updateAverages();

        Image image(10, 5);
        film.toImage(image);

        REQUIRE(image.channelNames() == std::vector<std::string>({"rgb", "test"}));
        REQUIRE_FALSE(image.rgb.isBlack());
        auto testChannel = image.getChannel("test");
        REQUIRE_FALSE(testChannel->isBlack());
        REQUIRE(testChannel->getPixelFormat() == PixelFormat::UINT8);
        REQUIRE(testChannel->getColorChannelCount() == 1);
    }

    SECTION("should convert custom Color3f channel") {
        auto customValueBuffer = new Color3fValueBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("test", customValueBuffer);

        film.addSample("color", {3, 3}, Color(1, 2, 3));
        film.addSample("test", {3, 3}, Color(1, 2, 3));
        film.updateAverages();

        Image image(10, 5);
        film.toImage(image);

        REQUIRE(image.channelNames() == std::vector<std::string>({"rgb", "test"}));
        REQUIRE_FALSE(image.rgb.isBlack());
        auto testChannel = image.getChannel("test");
        REQUIRE_FALSE(testChannel->isBlack());
        REQUIRE(testChannel->getPixelFormat() == PixelFormat::FLOAT32);
        REQUIRE(testChannel->getColorChannelCount() == 3);
    }

    SECTION("should convert custom Color3i channel") {
        auto customValueBuffer = new Color3iValueBuffer(10, 5);
        Film film(10, 5);
        film.addChannel("test", customValueBuffer);

        film.addSample("color", {3, 3}, Color(1, 2, 3));
        film.addSample("test", {3, 3}, Color(1, 2, 3));
        film.updateAverages();

        Image image(10, 5);
        film.toImage(image);

        REQUIRE(image.channelNames() == std::vector<std::string>({"rgb", "test"}));
        REQUIRE_FALSE(image.rgb.isBlack());
        auto testChannel = image.getChannel("test");
        REQUIRE_FALSE(testChannel->isBlack());
        REQUIRE(testChannel->getPixelFormat() == PixelFormat::UINT8);
        REQUIRE(testChannel->getColorChannelCount() == 3);
    }
}

}