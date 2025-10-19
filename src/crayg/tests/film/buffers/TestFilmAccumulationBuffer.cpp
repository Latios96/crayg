#include "crayg/image/film/buffers/FilmAccumulationBuffer.h"

#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("AccumulationBuffer::construct") {

    SECTION("should construct from dimensions and zero initialize") {
        const auto &testData = GENERATE(
            table<AccumulationBufferVariant>({FloatAccumulationBuffer(10, 5), Color3fAccumulationBuffer(10, 5)}));
        const auto &buffer = std::get<0>(testData);

        std::visit(
            [](auto &buf) {
                REQUIRE(buf.width == 10);
                REQUIRE(buf.height == 5);
                REQUIRE(buf.isBlack());
                // todo refactor to use for each when using Array2d
                for (int i = 0; i < buf.pixelCount(); i++) {
                    for (int c = 0; c < buf.chCount; c++) {
                        REQUIRE(buf.sum[i].value[c].get() == 0);
                    }
                    REQUIRE(buf.weight->get() == 0);
                }
            },
            buffer);
    }

    SECTION("should construct from resolution and zero initialize") {
        const auto &testData = GENERATE(table<AccumulationBufferVariant>(
            {FloatAccumulationBuffer(Resolution(10, 5)), Color3fAccumulationBuffer(Resolution(10, 5))}));
        const auto &buffer = std::get<0>(testData);

        std::visit(
            [](auto &buf) {
                REQUIRE(buf.width == 10);
                REQUIRE(buf.height == 5);
                REQUIRE(buf.isBlack());
                // todo refactor to use for each when using Array2d
                for (int i = 0; i < buf.pixelCount(); i++) {
                    for (int c = 0; c < buf.chCount; c++) {
                        REQUIRE(buf.sum[i].value[c].get() == 0);
                    }
                    REQUIRE(buf.weight->get() == 0);
                }
            },
            buffer);
    }
}

TEST_CASE("AccumulationBuffer::copy") {

    SECTION("should copy") {
        const auto &testData = GENERATE(table<AccumulationBufferVariant>({
            FloatAccumulationBuffer(10, 5),
            Color3fAccumulationBuffer(10, 5),
        }));
        const auto &buffer = std::get<0>(testData);

        std::visit(
            [](auto &originalBuffer) {
                const auto copy = originalBuffer;
                originalBuffer.data[0].value[0] = 1;
                originalBuffer.data[0].value[0] = 1;
                originalBuffer.sum[0].value[0].atomicAdd(1);
                originalBuffer.weight[0].atomicAdd(1);

                REQUIRE(copy.isBlack());
                REQUIRE(copy.sumIsZero());
                REQUIRE(copy.weightIsZero());
                REQUIRE_FALSE(originalBuffer.isBlack());
                REQUIRE_FALSE(originalBuffer.sumIsZero());
                REQUIRE_FALSE(originalBuffer.weightIsZero());
            },
            buffer);
    }
}

TEST_CASE("AccumulationBuffer::assignment") {

    SECTION("should assign from const") {
        const auto &testData = GENERATE(table<AccumulationBufferVariant>({
            FloatAccumulationBuffer(10, 5),
            Color3fAccumulationBuffer(10, 5),
        }));
        const auto &buffer = std::get<0>(testData);

        std::visit(
            [](auto &originalBuffer) {
                const auto copy1 = originalBuffer;
                auto copy2 = originalBuffer;

                copy2 = copy1;
                copy2.data[0].value[0] = 1;
                copy2.sum[0].value[0].atomicAdd(1);
                copy2.weight[0].atomicAdd(1);

                REQUIRE(copy1.isBlack());
                REQUIRE(copy1.sumIsZero());
                REQUIRE(copy1.weightIsZero());
                REQUIRE_FALSE(copy2.isBlack());
                REQUIRE_FALSE(copy2.sumIsZero());
                REQUIRE_FALSE(copy2.weightIsZero());
            },
            buffer);
    }

    SECTION("should assign from non-const") {
        const auto &testData = GENERATE(table<AccumulationBufferVariant>({
            FloatAccumulationBuffer(10, 5),
            Color3fAccumulationBuffer(10, 5),
        }));
        const auto &buffer = std::get<0>(testData);

        std::visit(
            [](auto &originalBuffer) {
                auto copy1 = originalBuffer;
                auto copy2 = originalBuffer;

                copy2 = copy1;
                copy2.data[0].value[0] = 1;
                copy2.sum[0].value[0].atomicAdd(1);
                copy2.weight[0].atomicAdd(1);

                REQUIRE(copy1.isBlack());
                REQUIRE(copy1.sumIsZero());
                REQUIRE(copy1.weightIsZero());
                REQUIRE_FALSE(copy2.isBlack());
                REQUIRE_FALSE(copy2.sumIsZero());
                REQUIRE_FALSE(copy2.weightIsZero());
            },
            buffer);
    }
}

TEST_CASE("AccumulationBuffer::sumIsConstant") {

    SECTION("should return true for black buffers") {
        const auto &testData = GENERATE(table<AccumulationBufferVariant>({
            FloatAccumulationBuffer(10, 5),
            Color3fAccumulationBuffer(10, 5),
        }));
        const auto &buffer = std::get<0>(testData);

        std::visit(
            [](auto &buf) {
                REQUIRE(buf.sumIsConstant(Color::createBlack()));
                REQUIRE(buf.sumIsConstant(0));
            },
            buffer);
    }

    SECTION("should return false for buffer with one black pixel") {
        const auto &testData = GENERATE(table<AccumulationBufferVariant>({
            FloatAccumulationBuffer(10, 5),
            Color3fAccumulationBuffer(10, 5),
        }));
        const auto &buffer = std::get<0>(testData);

        std::visit(
            [](auto &buf) {
                buf.sum[5].value[0].atomicAdd(1);
                REQUIRE_FALSE(buf.sumIsConstant(Color::createBlack()));
                REQUIRE_FALSE(buf.sumIsConstant(0));
            },
            buffer);
    }
}

TEST_CASE("AccumulationBuffer::weightIsConstant") {

    SECTION("should return true for black buffers") {
        const auto &testData = GENERATE(table<AccumulationBufferVariant>({
            FloatAccumulationBuffer(10, 5),
            Color3fAccumulationBuffer(10, 5),
        }));
        const auto &buffer = std::get<0>(testData);

        std::visit([](auto &buf) { REQUIRE(buf.weightIsConstant(0)); }, buffer);
    }

    SECTION("should return false for buffer with one black pixel") {
        const auto &testData = GENERATE(table<AccumulationBufferVariant>({
            FloatAccumulationBuffer(10, 5),
            Color3fAccumulationBuffer(10, 5),
        }));
        const auto &buffer = std::get<0>(testData);

        std::visit(
            [](auto &buf) {
                buf.weight[5].atomicAdd(1);
                REQUIRE_FALSE(buf.weightIsConstant(0));
            },
            buffer);
    }
}

TEST_CASE("AccumulationBuffer::add float"){

    SECTION("should add float correctly"){auto &testData = GENERATE(table<AccumulationBufferVariant>({
                                              FloatAccumulationBuffer(10, 5),
                                              Color3fAccumulationBuffer(10, 5),
                                          }));
auto buffer = std::get<0>(testData);

std::visit(
    [](auto &buf) {
        buf.add({4, 4}, 1);
        buf.add({4, 4}, 2);

        REQUIRE(buf.isBlack());
        REQUIRE(buf.sum[buf.index({4, 4})].value[0].get() == 3);
        REQUIRE(buf.weight[buf.index({4, 4})].get() == 2);
    },
    buffer);
}

#ifdef CRAYG_DEBUG_CHECKS

SECTION("should fail for invalid pixel") {
    const auto &testData =
        GENERATE(table<AccumulationBufferVariant>({FloatAccumulationBuffer(10, 5), Color3fAccumulationBuffer(10, 5)}));
    auto buffer = std::get<0>(testData);

    std::visit([](auto &buf) { REQUIRE_THROWS(buf.add({10, 10}, 1)); }, buffer);
}

#endif
}

TEST_CASE("AccumulationBuffer::add Color"){

    SECTION("should add Color correctly for FloatAccumulationBuffer"){FloatAccumulationBuffer buffer(10, 5);

buffer.add({4, 4}, Color(1, 2, 3));
buffer.add({4, 4}, Color(1, 2, 3));

REQUIRE(buffer.isBlack());
REQUIRE(buffer.sum[buffer.index({4, 4})].value[0].get() == 2);
REQUIRE(buffer.weight[buffer.index({4, 4})].get() == 2);
}

SECTION("should add Color correctly for Color3fAccumulationBuffer") {
    Color3fAccumulationBuffer buffer(10, 5);

    buffer.add({4, 4}, Color(1, 2, 3));
    buffer.add({4, 4}, Color(1, 2, 3));

    REQUIRE(buffer.isBlack());
    REQUIRE(buffer.sum[buffer.index({4, 4})].value[0].get() == 2);
    REQUIRE(buffer.sum[buffer.index({4, 4})].value[1].get() == 4);
    REQUIRE(buffer.sum[buffer.index({4, 4})].value[2].get() == 6);
    REQUIRE(buffer.weight[buffer.index({4, 4})].get() == 2);
}

#ifdef CRAYG_DEBUG_CHECKS

SECTION("should fail for invalid pixel") {
    const auto &testData =
        GENERATE(table<AccumulationBufferVariant>({FloatAccumulationBuffer(10, 5), Color3fAccumulationBuffer(10, 5)}));
    auto buffer = std::get<0>(testData);

    std::visit([](auto &buf) { REQUIRE_THROWS(buf.add({10, 10}, Color(1, 2, 3))); }, buffer);
}

#endif
}

TEST_CASE("AccumulationBuffer::updateAverages") {

    SECTION("should not end up with NaNs if weight is zero") {
        FloatAccumulationBuffer buffer(10, 5);
        REQUIRE(buffer.isBlack());
        REQUIRE(buffer.weightIsZero());

        buffer.updateAverages();

        REQUIRE_FALSE(buffer.getColor({0, 0}).hasNaN());
    }

    SECTION("should update average values correctly for FloatAccumulationBuffer") {
        FloatAccumulationBuffer buffer(10, 5);

        buffer.add({4, 4}, Color(1, 2, 3));
        buffer.add({4, 4}, Color(2, 4, 6));
        REQUIRE(buffer.isBlack());

        buffer.updateAverages();

        REQUIRE_FALSE(buffer.isBlack());
        REQUIRE(buffer.getColor({4, 4}) == Color(1.5, 1.5, 1.5));
    }

    SECTION("should update average values correctly for Color3fAccumulationBuffer") {
        Color3fAccumulationBuffer buffer(10, 5);

        buffer.add({4, 4}, Color(1, 2, 3));
        buffer.add({4, 4}, Color(2, 4, 6));

        REQUIRE(buffer.isBlack());
        buffer.updateAverages();
        REQUIRE_FALSE(buffer.isBlack());
        REQUIRE(buffer.getColor({4, 4}) == Color(1.5, 3, 4.5));
    }
}

TEST_CASE("AccumulationBuffer::updateAverages for Tile") {

    SECTION("should update average values correctly for FloatAccumulationBuffer") {
        FloatAccumulationBuffer buffer(10, 5);

        buffer.add({0, 0}, Color(1, 2, 3));
        buffer.add({2, 2}, Color(2, 4, 6));
        REQUIRE(buffer.isBlack());

        buffer.updateAveragesInTile(Tile(Vector2i(2, 2), 2, 2));

        REQUIRE_FALSE(buffer.isBlack());
        REQUIRE(buffer.getColor({0, 0}).isBlack());
        REQUIRE(buffer.getColor({2, 2}) == Color(2, 2, 2));
    }

    SECTION("should update average values correctly for Color3fAccumulationBuffer") {
        Color3fAccumulationBuffer buffer(10, 5);

        buffer.add({0, 0}, Color(1, 2, 3));
        buffer.add({2, 2}, Color(2, 4, 6));
        REQUIRE(buffer.isBlack());

        buffer.updateAveragesInTile(Tile(Vector2i(2, 2), 2, 2));

        REQUIRE_FALSE(buffer.isBlack());
        REQUIRE(buffer.getColor({0, 0}).isBlack());
        REQUIRE(buffer.getColor({2, 2}) == Color(2, 4, 6));
    }
}

TEST_CASE("AccumulationBuffer::getColor should work through BaseBuffer ptr") {

    SECTION("should write float correctly for FloatValueBuffer") {
        FloatAccumulationBuffer buffer(10, 5);
        FloatBufferBase *bufferBase = &buffer;

        buffer.add({0, 0}, 1);
        buffer.updateAverages();

        REQUIRE(bufferBase->getFloat({0, 0}) == 1);
        REQUIRE(bufferBase->getColor({0, 0}) == Color(1, 1, 1));
    }
}
}
