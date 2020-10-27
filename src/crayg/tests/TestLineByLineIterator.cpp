//
// Created by Jan Honsbrok on 28.10.18.
//

#include <catch2/catch.hpp>
#include <image/Image.h>
#include <image/ImageIterators.h>
#include <iostream>

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

    SECTION("testNotEqualIsEqual") {
        LineByLineIterator<Image> iterator(19, 0, image);
        LineByLineIterator<Image> otherIterator(19, 0, image);

        REQUIRE_FALSE(iterator != otherIterator);
    }
    SECTION("testEqual") {
        LineByLineIterator<Image> iterator(19, 0, image);
        LineByLineIterator<Image> otherIterator(19, 9, image);

        REQUIRE(iterator != otherIterator);
    }
    SECTION("testIterate") {
        std::vector<PixelPosition> positions;
        for (int y = 0; y < image.getHeight(); y++) {
            for (int x = 0; x < image.getWidth(); x++) {
                positions.push_back(PixelPosition(x, y));
            }
        }
        int counter = 0;
        for (auto pixel : ImageIterators::lineByLine(image)) {
            REQUIRE(pixel.x == positions[counter].x);
            REQUIRE(pixel.y == positions[counter].y);
            counter++;
        }
        REQUIRE(counter == 20 * 10 - 1);
    }
}