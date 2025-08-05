#include "basics/Resolution.h"
#include "image/film/buffers/FilmBufferBase.h"
#include "image/film/buffers/FilmValueTrait.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("BufferBase::construct") {

    SECTION("should construct from Dimensions") {
        const auto &testData = GENERATE(table<BufferBaseVariant>(
            {FloatBufferBase(10, 5), IntBufferBase(10, 5), Color3fBufferBase(10, 5), Color3iBufferBase(10, 5)}));
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
            table<BufferBaseVariant>({FloatBufferBase(Resolution(10, 5)), IntBufferBase(Resolution(10, 5)),
                                      Color3fBufferBase(Resolution(10, 5)), Color3iBufferBase(Resolution(10, 5))}));
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

TEST_CASE("BufferBase::copy") {

    SECTION("should copy") {
        const auto &testData = GENERATE(table<BufferBaseVariant>(
            {FloatBufferBase(10, 5), IntBufferBase(10, 5), Color3fBufferBase(10, 5), Color3iBufferBase(10, 5)}));
        const auto &buffer = std::get<0>(testData);

        std::visit(
            [](auto &originalBuffer) {
                const auto copy = originalBuffer;
                originalBuffer.data[0].value[0] = 1;

                REQUIRE(copy.isBlack());
                REQUIRE_FALSE(originalBuffer.isBlack());
            },
            buffer);
    }
}

TEST_CASE("BufferBase::assignment") {

    SECTION("should assign from const") {
        const auto &testData = GENERATE(table<BufferBaseVariant>(
            {FloatBufferBase(10, 5), IntBufferBase(10, 5), Color3fBufferBase(10, 5), Color3iBufferBase(10, 5)}));
        const auto &buffer = std::get<0>(testData);

        std::visit(
            [](auto &originalBuffer) {
                const auto copy1 = originalBuffer;
                auto copy2 = originalBuffer;

                copy2 = copy1;
                copy2.data[0].value[0] = 1;

                REQUIRE(copy1.isBlack());
                REQUIRE_FALSE(copy2.isBlack());
            },
            buffer);
    }

    SECTION("should assign from non-const") {
        const auto &testData = GENERATE(table<BufferBaseVariant>(
            {FloatBufferBase(10, 5), IntBufferBase(10, 5), Color3fBufferBase(10, 5), Color3iBufferBase(10, 5)}));
        const auto &buffer = std::get<0>(testData);

        std::visit(
            [](auto &originalBuffer) {
                auto copy1 = originalBuffer;
                auto copy2 = originalBuffer;

                copy2 = copy1;
                copy2.data[0].value[0] = 1;

                REQUIRE(copy1.isBlack());
                REQUIRE_FALSE(copy2.isBlack());
            },
            buffer);
    }
}

TEST_CASE("BufferBase::getFloat") {

    SECTION("should get float from FloatBufferBase") {
        FloatBufferBase buffer(10, 5);

        buffer.data[0].value[0] = 1;
        buffer.data[1].value[0] = 2;
        buffer.data[2].value[0] = 3;

        REQUIRE(buffer.getFloat({0, 0}) == 1);
        REQUIRE(buffer.getFloat({1, 0}) == 2);
        REQUIRE(buffer.getFloat({2, 0}) == 3);
    }

    SECTION("should get float from Color3fBufferBase") {
        Color3fBufferBase buffer(10, 5);

        buffer.data[0].value[0] = 1;
        buffer.data[0].value[1] = 2;
        buffer.data[0].value[2] = 3;

        REQUIRE(buffer.getFloat({0, 0}) == 1);
    }

    SECTION("should get float from IntBufferBase") {
        IntBufferBase buffer(10, 5);

        buffer.data[0].value[0] = 1;
        buffer.data[1].value[0] = 2;
        buffer.data[2].value[0] = 3;

        REQUIRE(buffer.getFloat({0, 0}) == Catch::Detail::Approx(0.003921569f));
    }

    SECTION("should get float from Color3iBufferBase") {
        Color3iBufferBase buffer(10, 5);

        buffer.data[0].value[0] = 1;
        buffer.data[0].value[1] = 2;
        buffer.data[0].value[2] = 3;

        REQUIRE(buffer.getFloat({0, 0}) == Catch::Detail::Approx(0.003921569f));
    }
}

TEST_CASE("BufferBase::getColor"){

    SECTION("should get color from FloatBufferBase"){FloatBufferBase buffer(10, 5);

buffer.data[0].value[0] = 1;
buffer.data[1].value[0] = 2;

REQUIRE(buffer.getColor({0, 0}) == Color(1, 1, 1));
REQUIRE(buffer.getColor({1, 0}) == Color(2, 2, 2));
}

SECTION("should get color from Color3fBufferBase") {
    Color3fBufferBase buffer(10, 5);

    buffer.data[0].value[0] = 1;
    buffer.data[0].value[1] = 2;
    buffer.data[0].value[2] = 3;

    REQUIRE(buffer.getColor({0, 0}) == Color(1, 2, 3));
}

SECTION("should get color from IntBufferBase") {
    IntBufferBase buffer(10, 5);

    buffer.data[0].value[0] = 1;
    buffer.data[1].value[0] = 2;
    buffer.data[2].value[0] = 3;

    REQUIRE(buffer.getColor({0, 0}) == Color(0.003921569f, 0.003921569f, 0.003921569f));
}

SECTION("should get color from Color3iBufferBase") {
    Color3iBufferBase buffer(10, 5);

    buffer.data[0].value[0] = 1;
    buffer.data[0].value[1] = 2;
    buffer.data[0].value[2] = 3;

    REQUIRE(buffer.getColor({0, 0}) == Color(0.003921569f, 0.007843138f, 0.011764706f));
}

#ifdef CRAYG_DEBUG_CHECKS

SECTION("should fail for invalid pixel") {
    const auto &testData = GENERATE(table<BufferBaseVariant>(
        {FloatBufferBase(10, 5), IntBufferBase(10, 5), Color3fBufferBase(10, 5), Color3iBufferBase(10, 5)}));
    const auto &buffer = std::get<0>(testData);

    std::visit(
        [](auto &buf) {
            REQUIRE_THROWS(buf.getFloat({10, 10}));
            REQUIRE_THROWS(buf.getColor({10, 10}));
        },
        buffer);
}

#endif
}

TEST_CASE("BufferBase::isColor") {

    SECTION("should return true for black buffers") {
        const auto &testData = GENERATE(table<BufferBaseVariant>(
            {FloatBufferBase(10, 5), IntBufferBase(10, 5), Color3fBufferBase(10, 5), Color3iBufferBase(10, 5)}));
        const auto &buffer = std::get<0>(testData);

        std::visit([](auto &buf) { REQUIRE(buf.isColor(Color::createBlack())); }, buffer);
    }

    SECTION("should return false for buffer with one black pixel") {
        const auto &testData = GENERATE(table<BufferBaseVariant>(
            {FloatBufferBase(10, 5), IntBufferBase(10, 5), Color3fBufferBase(10, 5), Color3iBufferBase(10, 5)}));
        const auto &buffer = std::get<0>(testData);

        std::visit(
            [](auto &buf) {
                buf.data[5].value[0] = 1;
                REQUIRE_FALSE(buf.isColor(Color::createBlack()));
            },
            buffer);
    }
}

TEST_CASE("BufferBase::describe") {

    SECTION("should describe BufferBase correctly") {
        const auto &testData =
            GENERATE(table<BufferBaseVariant, std::string>({{FloatBufferBase(10, 5), "1x f32"},
                                                            {IntBufferBase(10, 5), "1x uint8"},
                                                            {Color3fBufferBase(10, 5), "3x f32"},
                                                            {Color3iBufferBase(10, 5), "3x uint8"}}));
        const auto &buffer = std::get<0>(testData);
        const auto &description = std::get<1>(testData);

        std::visit([&description](auto &buf) { REQUIRE(buf.describe() == description); }, buffer);
    }
}
}