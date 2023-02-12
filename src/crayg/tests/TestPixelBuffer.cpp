#include <catch2/catch.hpp>
#include "image/PixelBuffer.h"

namespace crayg {

TEST_CASE("PixelBuffer::construct") {

    SECTION("should construct a PixelBuffer with given dimensions") {
        auto channelCount = GENERATE(1, 3);
        PixelBuffer pixelBuffer(5, 10, PixelFormat::FLOAT, channelCount);

        REQUIRE(pixelBuffer.getWidth() == 5);
        REQUIRE(pixelBuffer.getHeight() == 10);
        REQUIRE(pixelBuffer.getColorChannelCount() == channelCount);
        REQUIRE(pixelBuffer.isBlack());
    }

    SECTION("should construct a PixelBuffer with given resolution") {
        auto channelCount = GENERATE(1, 3);
        Resolution resolution(5, 10);
        PixelBuffer pixelBuffer(resolution, PixelFormat::FLOAT, channelCount);

        REQUIRE(pixelBuffer.getWidth() == 5);
        REQUIRE(pixelBuffer.getHeight() == 10);
        REQUIRE(pixelBuffer.getColorChannelCount() == channelCount);
        REQUIRE(pixelBuffer.isBlack());
    }
}

TEST_CASE("PixelBuffer::copy construct") {

    SECTION("should construct a UNIT8 PixelBuffer with given dimensions") {
        auto channelCount = GENERATE(1, 3);
        PixelBuffer pixelBuffer(5, 10, PixelFormat::UINT8, channelCount);
        pixelBuffer.setValue({2, 3}, Color::createWhite());

        PixelBuffer copy = pixelBuffer;

        REQUIRE(copy == pixelBuffer);
    }

    SECTION("should construct a FLOAT PixelBuffer with given resolution") {
        auto channelCount = GENERATE(1, 3);
        PixelBuffer pixelBuffer(5, 10, PixelFormat::FLOAT, channelCount);
        pixelBuffer.setValue({2, 3}, Color::createWhite());

        PixelBuffer copy = pixelBuffer;

        REQUIRE(copy == pixelBuffer);
    }
}

TEST_CASE("PixelBuffer::factory methods") {
    SECTION("createRgbFloat") {
        auto pixelBuffer = PixelBuffer::createRgbFloat(Resolution(5, 10));

        REQUIRE(pixelBuffer->getWidth() == 5);
        REQUIRE(pixelBuffer->getHeight() == 10);
        REQUIRE(pixelBuffer->getColorChannelCount() == 3);
        REQUIRE(pixelBuffer->isBlack());
    }

    SECTION("createGreyFloat") {
        auto pixelBuffer = PixelBuffer::createGreyFloat(Resolution(5, 10));

        REQUIRE(pixelBuffer->getWidth() == 5);
        REQUIRE(pixelBuffer->getHeight() == 10);
        REQUIRE(pixelBuffer->getColorChannelCount() == 1);
        REQUIRE(pixelBuffer->isBlack());
    }

    SECTION("createRgbUInt8") {
        auto pixelBuffer = PixelBuffer::createRgbUInt8(Resolution(5, 10));

        REQUIRE(pixelBuffer->getWidth() == 5);
        REQUIRE(pixelBuffer->getHeight() == 10);
        REQUIRE(pixelBuffer->getColorChannelCount() == 3);
        REQUIRE(pixelBuffer->isBlack());
    }

    SECTION("createGreyUInt8") {
        auto pixelBuffer = PixelBuffer::createGreyUInt8(Resolution(5, 10));

        REQUIRE(pixelBuffer->getWidth() == 5);
        REQUIRE(pixelBuffer->getHeight() == 10);
        REQUIRE(pixelBuffer->getColorChannelCount() == 1);
        REQUIRE(pixelBuffer->isBlack());
    }

    SECTION("createRgbFloat") {
        auto pixelBuffer = PixelBuffer::createVector3f(Resolution(5, 10));

        REQUIRE(pixelBuffer->getWidth() == 5);
        REQUIRE(pixelBuffer->getHeight() == 10);
        REQUIRE(pixelBuffer->getColorChannelCount() == 3);
        REQUIRE(pixelBuffer->isBlack());
    }
}

TEST_CASE("PixelBuffer::comparison") {

    SECTION("two buffers with same data ptr should be equal") {
        auto channelCount = GENERATE(1, 3);
        PixelBuffer pixelBuffer(5, 10, PixelFormat::FLOAT, channelCount);

        REQUIRE(pixelBuffer == pixelBuffer);
    }

    SECTION("two black buffers should be equal") {
        auto channelCount = GENERATE(1, 3);
        PixelBuffer left(5, 10, PixelFormat::FLOAT, channelCount);
        PixelBuffer right(5, 10, PixelFormat::FLOAT, channelCount);

        REQUIRE(left == right);
    }

    SECTION("black and black with one white pixel should not be equal") {
        auto channelCount = GENERATE(1, 3);
        PixelBuffer left(5, 10, PixelFormat::FLOAT, channelCount);
        PixelBuffer right(5, 10, PixelFormat::FLOAT, channelCount);
        right.setValue({2, 3}, Color::createWhite());

        REQUIRE(left != right);
    }

    SECTION("black and white buffer should not be equal") {
        auto channelCount = GENERATE(1, 3);
        PixelBuffer black(5, 10, PixelFormat::FLOAT, channelCount);
        PixelBuffer white(5, 10, PixelFormat::FLOAT, channelCount);
        white.fill(Color::createWhite());

        REQUIRE(black != white);
    }

    SECTION("different resolution should not be equal") {
        PixelBuffer left(5, 10, PixelFormat::FLOAT, 3);
        PixelBuffer right(5, 11, PixelFormat::FLOAT, 3);

        REQUIRE(left != right);
    }

    SECTION("different channel count should not be equal") {
        PixelBuffer left(5, 10, PixelFormat::FLOAT, 1);
        PixelBuffer right(5, 10, PixelFormat::FLOAT, 3);

        REQUIRE(left != right);
    }

    SECTION("different pixel format should not be equal") {
        PixelBuffer left(5, 10, PixelFormat::FLOAT, 3);
        PixelBuffer right(5, 10, PixelFormat::UINT8, 3);

        REQUIRE(left != right);
    }
}

TEST_CASE("PixelBuffer::fill") {
    SECTION("should fill buffer with color") {
        auto channelCount = GENERATE(1, 3);
        PixelBuffer pixelBuffer(5, 10, PixelFormat::FLOAT, channelCount);

        pixelBuffer.fill(Color::createGrey(0.5f));

        REQUIRE(pixelBuffer.isColor(Color::createGrey(0.5f)));
    }
}

TEST_CASE("PixelBuffer::isColor") {
    SECTION("should return true") {
        auto channelCount = GENERATE(1, 3);
        PixelBuffer pixelBuffer(5, 10, PixelFormat::FLOAT, channelCount);

        pixelBuffer.fill(Color::createGrey(0.5f));

        REQUIRE(pixelBuffer.isColor(Color::createGrey(0.5f)));
    }

    SECTION("should return false") {
        auto channelCount = GENERATE(1, 3);
        PixelBuffer pixelBuffer(5, 10, PixelFormat::FLOAT, channelCount);

        REQUIRE_FALSE(pixelBuffer.isColor(Color::createGrey(0.5f)));
    }
}

TEST_CASE("PixelBuffer::get/setValue") {
    SECTION("should set color and return float color ") {
        auto channelCount = GENERATE(1, 3);
        PixelBuffer pixelBuffer(5, 10, PixelFormat::FLOAT, channelCount);

        pixelBuffer.setValue({2, 3}, Color::createGrey(0.1f));

        REQUIRE(pixelBuffer.getValue({2, 3}) == Color::createGrey(0.1f));
    }

    SECTION("should set color and return UInt8 color") {
        auto channelCount = GENERATE(1, 3);
        PixelBuffer pixelBuffer(5, 10, PixelFormat::UINT8, channelCount);

        pixelBuffer.setValue({2, 3}, Color::createWhite());

        REQUIRE(pixelBuffer.getValue({2, 3}) == Color::createWhite());
    }
}

TEST_CASE("PixelBuffer::formatting") {

    SECTION("should format to ostream") {
        std::ostringstream os;
        PixelBuffer pixelBuffer(5, 10, PixelFormat::FLOAT, 3);

        os << pixelBuffer;

        REQUIRE(os.str() == "PixelBuffer{width=5,height=10,colorChannelCount=3,pixelFormat=FLOAT}");
    }

    SECTION("should format using fmt") {
        PixelBuffer pixelBuffer(5, 10, PixelFormat::FLOAT, 3);

        REQUIRE(
            fmt::format("{}", pixelBuffer) == "PixelBuffer{width=5,height=10,colorChannelCount=3,pixelFormat=FLOAT}");
    }
}

}