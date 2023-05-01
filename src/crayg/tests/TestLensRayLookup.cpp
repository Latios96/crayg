#include "scene/camera/lookup/LensRayLookupTable.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("LensRayLookupTable::getVec3fIndex") {

    SECTION("should ") {
        LensRayLookupTable lensRayLookupTable(Resolution(10, 5), 2);

        REQUIRE(lensRayLookupTable.getVec3fIndex({0, 0}, 0, 0) == 0);
        REQUIRE(lensRayLookupTable.getVec3fIndex({0, 0}, 0, 1) == 1);
        REQUIRE(lensRayLookupTable.getVec3fIndex({0, 0}, 1, 0) == 2);
        REQUIRE(lensRayLookupTable.getVec3fIndex({0, 0}, 1, 1) == 3);
        REQUIRE(lensRayLookupTable.getVec3fIndex({1, 0}, 0, 0) == 4);
        REQUIRE(lensRayLookupTable.getVec3fIndex({1, 0}, 0, 1) == 5);
        REQUIRE(lensRayLookupTable.getVec3fIndex({1, 0}, 1, 0) == 6);
        REQUIRE(lensRayLookupTable.getVec3fIndex({1, 0}, 1, 1) == 7);
        REQUIRE(lensRayLookupTable.getVec3fIndex({0, 1}, 0, 0) == 40);
        REQUIRE(lensRayLookupTable.getVec3fIndex({0, 1}, 0, 1) == 41);
        int index = -1;
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 10; x++) {
                for (int i = 0; i < 2; i++) {
                    REQUIRE(lensRayLookupTable.getVec3fIndex({x, y}, i, 0) == index + 1);
                    REQUIRE(lensRayLookupTable.getVec3fIndex({x, y}, i, 1) == index + 2);
                    index += 2;
                }
            }
        }
        REQUIRE(index == 10 * 5 * 2 * 2 - 1);

        lensRayLookupTable.dirs.resize(5);
        lensRayLookupTable.dirs[lensRayLookupTable.getVec3fIndex({0, 0}, 0, 0)] = Vector3f(1, 2, 3);
        lensRayLookupTable.dirs[lensRayLookupTable.getVec3fIndex({0, 0}, 0, 0) + 1] = Vector3f(4, 5, 6);

        REQUIRE(lensRayLookupTable.dirs[0] == Vector3f(1, 2, 3));
        REQUIRE(lensRayLookupTable.dirs[1] == Vector3f(4, 5, 6));
    }
}

}