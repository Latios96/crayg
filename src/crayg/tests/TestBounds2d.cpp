#include "basics/Bound2d.h"
#include <catch2/catch.hpp>
#include <sstream>

namespace crayg {

TEST_CASE("Bounds2d::construct") {

    SECTION("should default construct") {
        Bounds2df bounds2Df;

        REQUIRE(bounds2Df == Bounds2df({0, 0}, {0, 0}));
    }

    SECTION("should construct with params") {
        Bounds2df bounds2Df({1, 2}, {3, 4});

        REQUIRE(bounds2Df == Bounds2df({1, 2}, {3, 4}));
    }

    SECTION("should copy construct") {
        const Bounds2df bounds2Df({1, 2}, {3, 4});
        Bounds2df copy = bounds2Df;

        REQUIRE(copy == bounds2Df);
    }
}

TEST_CASE("Bounds2d::union with Vector2") {
    SECTION("Bounds2df should union with Vector2f") {
        Bounds2df bounds2Df;
        auto unionBounds = bounds2Df.unionWith(Vector2f(-1, 1));

        REQUIRE(unionBounds == Bounds2df({-1, 0}, {0, 1}));
    }

    SECTION("Bounds2df should union with Vector2i") {
        Bounds2df bounds2Df;
        auto unionBounds = bounds2Df.unionWith(Vector2i(-1, 1));

        REQUIRE(unionBounds == Bounds2df({-1, 0}, {0, 1}));
    }

    SECTION("Bounds2di should union with Vector2f") {
        Bounds2di bounds2Df;
        auto unionBounds = bounds2Df.unionWith(Vector2f(-1, 1));

        REQUIRE(unionBounds == Bounds2di({-1, 0}, {0, 1}));
    }

    SECTION("Bounds2di should union with Vector2i") {
        Bounds2di bounds2Df;
        auto unionBounds = bounds2Df.unionWith(Vector2i(-1, 1));

        REQUIRE(unionBounds == Bounds2di({-1, 0}, {0, 1}));
    }
}

TEST_CASE("Bounds2d::union with Bounds") {
    SECTION("Bounds2df should union with Bounds2df") {
        Bounds2df bounds2Df;
        auto unionBounds = bounds2Df.unionWith(Bounds2df({-1, 0}, {0, 1}));

        REQUIRE(unionBounds == Bounds2df({-1, 0}, {0, 1}));
    }

    SECTION("Bounds2df should union with Bounds2di") {
        Bounds2df bounds2Df;
        auto unionBounds = bounds2Df.unionWith(Bounds2di({-1, 0}, {0, 1}));

        REQUIRE(unionBounds == Bounds2df({-1, 0}, {0, 1}));
    }

    SECTION("Bounds2di should union with Bounds2df") {
        Bounds2di bounds2Df;
        auto unionBounds = bounds2Df.unionWith(Bounds2df({-1, 0}, {0, 1}));

        REQUIRE(unionBounds == Bounds2di({-1, 0}, {0, 1}));
    }

    SECTION("Bounds2di should union with Bounds2di") {
        Bounds2di bounds2Df;
        auto unionBounds = bounds2Df.unionWith(Bounds2di({-1, 0}, {0, 1}));

        REQUIRE(unionBounds == Bounds2di({-1, 0}, {0, 1}));
    }
}

TEST_CASE("Bounds2d::expand") {
    SECTION("Bounds2df should expand by Vector2f") {
        Bounds2df bounds2Df;
        auto expandedBounds = bounds2Df.expand(Vector2f(1, 2));

        REQUIRE(expandedBounds == Bounds2df({-1, -2}, {1, 2}));
    }
}

TEST_CASE("Bounds2d::lerp") {
    SECTION("should return min") {
        Bounds2df bounds2Df({0, 0}, {1, 1});

        auto lerped = bounds2Df.lerp(0, 0);

        REQUIRE(lerped == bounds2Df.min);
    }

    SECTION("should return max") {
        Bounds2df bounds2Df({0, 0}, {1, 1});

        auto lerped = bounds2Df.lerp(1, 1);

        REQUIRE(lerped == bounds2Df.max);
    }

    SECTION("should return value inbetween") {
        Bounds2df bounds2Df({0, 0}, {1, 1});

        auto lerped = bounds2Df.lerp(0.5f, 0.5f);

        REQUIRE(lerped == Vector2f(.5f, .5f));
    }
}

TEST_CASE("Bounds2d::equality") {
    SECTION("should be equal") {
        Bounds2df left;
        Bounds2df right;

        REQUIRE(left == right);
    }

    SECTION("different min should not be equal") {
        Bounds2df left({-1, 0}, {0, 0});
        Bounds2df right;

        REQUIRE(left != right);
    }

    SECTION("different max should not be equal") {
        Bounds2df left({0, 0}, {-1, 0});
        Bounds2df right;

        REQUIRE(left != right);
    }
}

TEST_CASE("Bounds2d::formatting") {
    SECTION("should be ostreamable") {
        std::ostringstream os;
        Bounds2df bounds2Df({1, 2}, {3, 4});

        os << bounds2Df;

        REQUIRE(os.str() == "Bounds2d{min=Vector2{x=1,y=2},max=Vector2{x=3,y=4}}");
    }

    SECTION("should be formatable") {
        Bounds2df bounds2Df({1, 2}, {3, 4});

        REQUIRE(fmt::format("{}", bounds2Df) == "Bounds2d{min=Vector2{x=1,y=2},max=Vector2{x=3,y=4}}");
    }
}

}