#include <catch2/catch.hpp>
#include <image/Image.h>
#include <image/imageiterators/pixels/ImageIterators.h>

namespace crayg {

TEST_CASE("LineByLineIterator", "[LineByLineIterator]") {
    Image image(20, 10);

    SECTION("testIncrementNormal") {
        LineByLineIterator<Image> iterator(0, 0, image);
        ++iterator;
        REQUIRE((*iterator).x == 1);
        REQUIRE((*iterator).y == 0);
    }

    SECTION("testIncrementLineEnd") {
        LineByLineIterator<Image> iterator(19, 0, image);
        ++iterator;
        REQUIRE((*iterator).x == 0);
        REQUIRE((*iterator).y == 1);
    }

    SECTION("testEqual") {
        LineByLineIterator<Image> iterator(19, 0, image);
        LineByLineIterator<Image> otherIterator(19, 9, image);

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
        for (auto pixel : ImageIterators::lineByLine(image)) {
            REQUIRE(pixel.x == positions[counter].x);
            REQUIRE(pixel.y == positions[counter].y);
            counter++;
        }
        REQUIRE(counter == 20 * 10);
    }
}

}