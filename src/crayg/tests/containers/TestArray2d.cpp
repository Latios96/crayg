#include "basics/containers/Array2d.h"
#include <catch2/catch.hpp>

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
}

TEST_CASE("Array2d::get") {
    SECTION("should return desired element") {
        Array2d<int> array2d(2, 3);

        array2d.get(0, 2) = 1;
        array2d.get(1, 2) = 5;
        REQUIRE(array2d.get(0, 2) == 1);
        REQUIRE(array2d.get(1, 2) == 5);
    }
}

TEST_CASE("Array2d::set") {
    SECTION("should return desired element") {
        Array2d<int> array2d(2, 3);

        array2d.set(0, 2, 1);
        array2d.set(1, 2, 5);
        REQUIRE(array2d.get(0, 2) == 1);
        REQUIRE(array2d.get(1, 2) == 5);
    }
}

TEST_CASE("Array2d::iterate") {
    SECTION("should visit all pixels") {
        Array2d<int> array2d(2, 3);

        int counter = 0;
        for (auto pixelValue : array2d) {
            counter++;
        }

        REQUIRE(counter == 6);
    }
}

}