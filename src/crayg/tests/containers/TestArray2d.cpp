#include "crayg/foundation/containers/Array2d.h"
#include <catch2/catch.hpp>
#include <numeric>

namespace crayg {

TEST_CASE("Array2d::construct") {
    SECTION("should default construct to size 0") {
        Array2d<int> array2d;

        REQUIRE(array2d.size() == 0);
        REQUIRE(array2d.data() == nullptr);
    }

    SECTION("should default construct given size") {
        Array2d<int> array2d(2, 3);

        REQUIRE(array2d.size() == 6);
        REQUIRE(array2d.data() != nullptr);
        REQUIRE(array2d.data()[0] == 0);
    }

    SECTION("should construct from initializer list") {
        Array2d<float> array2d(3, 3, {0.5, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 0.5});

        REQUIRE(array2d == Array2d<float>(3, 3, {0.5, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 0.5}));
    }

    SECTION("should construct from data ptr") {
        std::vector<float> dataToConstructFrom({0.5, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 0.5});
        Array2d<float> array2d(3, 3, dataToConstructFrom.data());

        REQUIRE(array2d == Array2d<float>(3, 3, {0.5, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 0.5}));
    }

    SECTION("should fail if initializer list does not match width and height") {
        REQUIRE_THROWS(Array2d<float>(3, 3, {0.5, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5}));
    }
}

TEST_CASE("Array2d::get") {
    SECTION("should return desired element") {
        Array2d<int> array2d(2, 3);

        array2d[{0, 2}] = 1;
        array2d[{1, 2}] = 5;
        REQUIRE(array2d[{0, 2}] == 1);
        REQUIRE(array2d[{1, 2}] == 5);
    }
}

TEST_CASE("Array2d::set") {
    SECTION("should return desired element") {
        Array2d<int> array2d(2, 3);

        array2d[{0, 2}] = 1;
        array2d[{1, 2}] = 5;
        REQUIRE(array2d[{0, 2}] == 1);
        REQUIRE(array2d[{1, 2}] == 5);
    }
}

TEST_CASE("Array2d::comparison") {
    SECTION("should be equal") {
        Array2d<float> array2d(3, 3, {0.5, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 0.5});

        REQUIRE(array2d == Array2d<float>(3, 3, {0.5, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 0.5}));
    }

    SECTION("should not be equal") {
        Array2d<float> array2d(3, 3, {0.5, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 0.5});

        REQUIRE_FALSE(array2d == Array2d<float>(3, 3, {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5}));
    }
}

TEST_CASE("Array2d::iterate") {
    SECTION("should compute sum of all values") {
        Array2d<float> array2d(3, 3, {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5});

        const float sum = std::accumulate(array2d.begin(), array2d.end(), 0.f);

        REQUIRE(sum == 4.5f);
    }

    SECTION("should iterate over all values") {
        Array2d<float> array2d(3, 3, {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5});

        float sum = 0;
        for (auto &v : array2d) {
            sum += v;
        }

        REQUIRE(sum == 4.5f);
    }
}

}