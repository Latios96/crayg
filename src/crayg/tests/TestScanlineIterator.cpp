#include "crayg/foundation/areaiterators/AreaIterators.h"
#include "crayg/image/Image.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("ScanlineIterator", "[ScanlineIterator]") {
    Image image(20, 10);

    SECTION("testIncrementNormal") {
        ScanlineIterator<Image> iterator(0, 0, image);
        ++iterator;
        REQUIRE((*iterator).x == 1);
        REQUIRE((*iterator).y == 0);
    }

    SECTION("testIncrementLineEnd") {
        ScanlineIterator<Image> iterator(19, 0, image);
        ++iterator;
        REQUIRE((*iterator).x == 0);
        REQUIRE((*iterator).y == 1);
    }

    SECTION("testEqual") {
        ScanlineIterator<Image> iterator(19, 0, image);
        ScanlineIterator<Image> otherIterator(19, 9, image);

        REQUIRE(iterator != otherIterator);
    }

    SECTION("testIterate") {
        std::vector<Vector2i> positions;
        for (int y = 0; y < image.getHeight(); y++) {
            for (int x = 0; x < image.getWidth(); x++) {
                positions.emplace_back(x, y);
            }
        }
        int counter = 0;
        for (auto pixel : AreaIterators::scanlines(image)) {
            REQUIRE(pixel.x == positions[counter].x);
            REQUIRE(pixel.y == positions[counter].y);
            counter++;
        }
        REQUIRE(counter == 20 * 10);
    }
}

}