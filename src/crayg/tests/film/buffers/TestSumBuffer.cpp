#include "crayg/foundation/math/geometry/Resolution.h"
#include "image/film/buffers/FilmSumBuffer.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("SumBuffer::construct") {

    SECTION("should construct from Dimensions") {
        const auto &testData = GENERATE(table<SumBufferVariant>(
            {FloatSumBuffer(10, 5), IntSumBuffer(10, 5), Color3fSumBuffer(10, 5), Color3iSumBuffer(10, 5)}));
        const auto &buffer = std::get<0>(testData);

        std::visit(
            [](auto &buf) {
                REQUIRE(buf.width == 10);
                REQUIRE(buf.height == 5);
                REQUIRE(buf.isBlack());
            },
            buffer);
    }

    SECTION("should construct from Resolution") {
        const auto &testData = GENERATE(
            table<SumBufferVariant>({FloatSumBuffer(Resolution(10, 5)), IntSumBuffer(Resolution(10, 5)),
                                     Color3fSumBuffer(Resolution(10, 5)), Color3iSumBuffer(Resolution(10, 5))}));
        const auto &buffer = std::get<0>(testData);

        std::visit(
            [](auto &buf) {
                REQUIRE(buf.width == 10);
                REQUIRE(buf.height == 5);
                REQUIRE(buf.isBlack());
            },
            buffer);
    }
}

TEST_CASE("SumBuffer::add Float") {

    SECTION("should add float correctly for FloatSumBuffer") {
        FloatSumBuffer buffer(10, 5);

        buffer.add({0, 0}, 1);

        REQUIRE(buffer.getFloat({0, 0}) == 1);
        REQUIRE(buffer.getColor({0, 0}) == Color(1, 1, 1));
    }

    SECTION("should add float correctly for IntSumBuffer") {
        IntSumBuffer buffer(10, 5);

        buffer.add({0, 0}, 0.5);
        buffer.add({0, 0}, 0.5);

        const float value = buffer.getFloat({0, 0});
        REQUIRE((value > 0.996 && value <= 1));
    }

    SECTION("should add float correctly for Color3fSumBuffer") {
        Color3fSumBuffer buffer(10, 5);

        buffer.add({0, 0}, 1);

        REQUIRE(buffer.getFloat({0, 0}) == 1);
        REQUIRE(buffer.getColor({0, 0}) == Color(1, 0, 0));
    }

    SECTION("should add float correctly for Color3iSumBuffer") {
        Color3iSumBuffer buffer(10, 5);

        buffer.add({0, 0}, 1);

        REQUIRE(buffer.getFloat({0, 0}) == 1);
        REQUIRE(buffer.getFloat({0, 0}) == 1);
        REQUIRE(buffer.getColor({0, 0}) == Color(1, 0, 0));
    }
}

TEST_CASE("SumBuffer::add Color"){

    SECTION("should add color correctly for FloatSumBuffer"){FloatSumBuffer buffer(10, 5);

buffer.add({0, 0}, Color(1, 2, 3));

REQUIRE(buffer.getFloat({0, 0}) == 1);
REQUIRE(buffer.getColor({0, 0}) == Color(1, 1, 1));
}

SECTION("should add color correctly for IntSumBuffer") {
    IntSumBuffer buffer(10, 5);

    buffer.add({0, 0}, Color(1, 2, 3));

    REQUIRE(buffer.getFloat({0, 0}) == 1);
    REQUIRE(buffer.getColor({0, 0}) == Color(1, 1, 1));
}

SECTION("should add color correctly for Color3fSumBuffer") {
    Color3fSumBuffer buffer(10, 5);

    buffer.add({0, 0}, Color(1, 2, 3));

    REQUIRE(buffer.getFloat({0, 0}) == 1);
    REQUIRE(buffer.getColor({0, 0}) == Color(1, 2, 3));
}

SECTION("should add color correctly for Color3iSumBuffer") {
    Color3iSumBuffer buffer(10, 5);

    buffer.add({0, 0}, Color(1, 2, 3));

    REQUIRE(buffer.getFloat({0, 0}) == 1);
    REQUIRE(buffer.getColor({0, 0}) == Color(1, 1, 1));
}

#ifdef CRAYG_DEBUG_CHECKS

SECTION("should fail for invalid pixel") {
    const auto &testData = GENERATE(table<SumBufferVariant>(
        {FloatSumBuffer(10, 5), IntSumBuffer(10, 5), Color3fSumBuffer(10, 5), Color3iSumBuffer(10, 5)}));
    auto buffer = std::get<0>(testData);

    std::visit(
        [](auto &buf) {
            REQUIRE_THROWS(buf.add({10, 10}, Color(1, 2, 3)));
            REQUIRE_THROWS(buf.add({10, 10}, 1));
        },
        buffer);
}

#endif
}

TEST_CASE("SumBuffer::getColor should work through BaseBuffer ptr") {

    SECTION("should add float correctly for FloatSumBuffer") {
        FloatSumBuffer buffer(10, 5);
        FloatBufferBase *bufferBase = &buffer;

        buffer.add({0, 0}, 1);

        REQUIRE(bufferBase->getFloat({0, 0}) == 1);
        REQUIRE(bufferBase->getColor({0, 0}) == Color(1, 1, 1));
    }
}
}