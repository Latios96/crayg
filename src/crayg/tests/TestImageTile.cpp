#include "catch2/catch.hpp"
#include <image/ImageTile.h>

namespace crayg {

struct ImageWrapper {
    Image image;
};

TEST_CASE("ImageTile") {

    SECTION("shouldConstructCorrectly") {
        ImageTile imageTile({0, 1}, 20, 30);

        REQUIRE(imageTile.tile.getPosition() == Vector2i(0, 1));
        REQUIRE(imageTile.tile.getWidth() == 20);
        REQUIRE(imageTile.tile.getHeight() == 30);
        REQUIRE(imageTile.image.getWidth() == 20);
        REQUIRE(imageTile.image.getHeight() == 30);
    }
}

}
