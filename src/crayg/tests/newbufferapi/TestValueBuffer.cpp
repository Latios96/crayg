#include "basics/Resolution.h"
#include "image/newbufferapi/ValueBuffer.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("ValueBuffer::construct") {

    SECTION("should construct from Dimensions") {
        const auto &testData = GENERATE(table<ValueBufferVariant>(
            {FloatValueBuffer(10, 5), IntValueBuffer(10, 5), Color3fValueBuffer(10, 5), Color3iValueBuffer(10, 5)}));
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
            table<ValueBufferVariant>({FloatValueBuffer(Resolution(10, 5)), IntValueBuffer(Resolution(10, 5)),
                                       Color3fValueBuffer(Resolution(10, 5)), Color3iValueBuffer(Resolution(10, 5))}));
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

TEST_CASE("ValueBuffer::writeFloat") {

    SECTION("should write float correctly for FloatValueBuffer") {
        FloatValueBuffer buffer(10, 5);

        buffer.write({0, 0}, 1);

        REQUIRE(buffer.getFloat({0, 0}) == 1);
        REQUIRE(buffer.getColor({0, 0}) == Color(1, 0, 0));
    }

    SECTION("should write float correctly for IntValueBuffer") {
        IntValueBuffer buffer(10, 5);

        buffer.write({0, 0}, 1);
        buffer.write({0, 0}, 2);

        REQUIRE(buffer.getFloat({0, 0}) == 1);
        REQUIRE(buffer.getFloat({0, 0}) == 1);
        REQUIRE(buffer.getColor({0, 0}) == Color(1, 0, 0));
    }

    SECTION("should write float correctly for Color3fValueBuffer") {
        Color3fValueBuffer buffer(10, 5);

        buffer.write({0, 0}, 1);

        REQUIRE(buffer.getFloat({0, 0}) == 1);
        REQUIRE(buffer.getColor({0, 0}) == Color(1, 0, 0));
    }

    SECTION("should write float correctly for Color3iValueBuffer") {
        Color3iValueBuffer buffer(10, 5);

        buffer.write({0, 0}, 1);

        REQUIRE(buffer.getFloat({0, 0}) == 1);
        REQUIRE(buffer.getFloat({0, 0}) == 1);
        REQUIRE(buffer.getColor({0, 0}) == Color(1, 0, 0));
    }
}

TEST_CASE("ValueBuffer::writeColor"){

    SECTION("should write color correctly for FloatValueBuffer"){FloatValueBuffer buffer(10, 5);

buffer.write({0, 0}, Color(1, 2, 3));

REQUIRE(buffer.getFloat({0, 0}) == 1);
REQUIRE(buffer.getColor({0, 0}) == Color(1, 0, 0));
}

SECTION("should write color correctly for IntValueBuffer") {
    IntValueBuffer buffer(10, 5);

    buffer.write({0, 0}, Color(1, 2, 3));

    REQUIRE(buffer.getFloat({0, 0}) == 1);
    REQUIRE(buffer.getColor({0, 0}) == Color(1, 0, 0));
}

SECTION("should write color correctly for Color3fValueBuffer") {
    Color3fValueBuffer buffer(10, 5);

    buffer.write({0, 0}, Color(1, 2, 3));

    REQUIRE(buffer.getFloat({0, 0}) == 1);
    REQUIRE(buffer.getColor({0, 0}) == Color(1, 2, 3));
}

SECTION("should write color correctly for Color3iValueBuffer") {
    Color3iValueBuffer buffer(10, 5);

    buffer.write({0, 0}, Color(1, 2, 3));

    REQUIRE(buffer.getFloat({0, 0}) == 1);
    REQUIRE(buffer.getColor({0, 0}) == Color(1, 1, 1));
}

#ifdef CRAYG_DEBUG_CHECKS

SECTION("should fail for invalid pixel") {
    const auto &testData = GENERATE(table<ValueBufferVariant>(
        {FloatValueBuffer(10, 5), IntValueBuffer(10, 5), Color3fValueBuffer(10, 5), Color3iValueBuffer(10, 5)}));
    auto buffer = std::get<0>(testData);

    std::visit(
        [](auto &buf) {
            REQUIRE_THROWS(buf.write({10, 10}, Color(1, 2, 3)));
            REQUIRE_THROWS(buf.write({10, 10}, 1));
        },
        buffer);
}

#endif
}

TEST_CASE("ValueBuffer::getColor should work through BaseBuffer ptr") {

    SECTION("should write float correctly for FloatValueBuffer") {
        FloatValueBuffer buffer(10, 5);
        FloatBufferBase *bufferBase = &buffer;

        buffer.write({0, 0}, 1);

        REQUIRE(bufferBase->getFloat({0, 0}) == 1);
        REQUIRE(bufferBase->getColor({0, 0}) == Color(1, 0, 0));
    }
}
}