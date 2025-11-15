#include "crayg/foundation/math/geometry/Bound2d.h"
#include "crayg/foundation/math/geometry/Bound2d_formatter.h"
#include "crayg/foundation/math/geometry/Resolution.h"
#include <catch2/catch.hpp>
#include <sstream>

namespace crayg {

TEST_CASE("Bounds2d::construct") {
    SECTION("should default construct") {
        Bounds2df bounds2Df;

        REQUIRE(bounds2Df == Bounds2df({std::numeric_limits<float>::max(), std::numeric_limits<float>::max()},
                                       {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()}));
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

TEST_CASE("Bounds2d::deduce") {

    SECTION("should deduce correctly for int") {
        const Bounds2di bounds = Bounds2di::deduce(Resolution(1920, 1080));

        REQUIRE(bounds == Bounds2di(Vector2i(0, 0), Vector2i(1919, 1079)));
    }

    SECTION("should deduce correctly for float") {
        const Bounds2df bounds = Bounds2df::deduce(Resolution(1920, 1080));

        REQUIRE(bounds == Bounds2df(Vector2f(0, 0), Vector2f(1919, 1079)));
    }
}

TEST_CASE("Bounds2d::union with Vector2") {
    SECTION("default constructed Bounds2df should union with Vector2f") {
        Bounds2df bounds2Df;
        auto unionBounds = bounds2Df.unionWith(Vector2f(-1, 1));

        REQUIRE(unionBounds == Bounds2df({-1, 1}, {-1, 1}));
    }

    SECTION("default constructed Bounds2df should union with Vector2i") {
        Bounds2df bounds2Df;
        auto unionBounds = bounds2Df.unionWith(Vector2i(-1, 1));

        REQUIRE(unionBounds == Bounds2df({-1, 1}, {-1, 1}));
    }

    SECTION("Bounds2df should union with Vector2f") {
        Bounds2df bounds2Df(Vector2f(0), Vector2f(0));
        auto unionBounds = bounds2Df.unionWith(Vector2f(-1, 1));

        REQUIRE(unionBounds == Bounds2df({-1, 0}, {0, 1}));
    }

    SECTION("Bounds2di should union with Vector2i") {
        Bounds2di bounds2Di(Vector2i(0), Vector2i(0));
        auto unionBounds = bounds2Di.unionWith(Vector2i(-1, 1));

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
        Bounds2df bounds2Df({0, 0}, {0, 0});
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

TEST_CASE("Bounds2d::contains") {
    SECTION("Bounds2df should contain Vector2f") {
        Bounds2df bounds2Df({-1, -2}, {2, 1});

        REQUIRE(bounds2Df.contains(Vector2f(0, 0)));
    }

    SECTION("Bounds2df should not contain Vector2f") {
        Bounds2df bounds2Df({-1, -2}, {2, 1});

        REQUIRE_FALSE(bounds2Df.contains(Vector2f(2, 2)));
    }

    SECTION("Bounds2df should contain Vector2i") {
        Bounds2df bounds2Df({-1, -2}, {2, 1});

        REQUIRE(bounds2Df.contains(Vector2i(0, 0)));
    }

    SECTION("Bounds2df should not contain Vector2i") {
        Bounds2df bounds2Df({-1, -2}, {2, 1});

        REQUIRE_FALSE(bounds2Df.contains(Vector2i(2, 2)));
    }

    SECTION("Bounds2di should contain Vector2f") {
        Bounds2di bounds2Df({-1, -2}, {2, 1});

        REQUIRE(bounds2Df.contains(Vector2f(0, 0)));
    }

    SECTION("Bounds2di should not contain Vector2f") {
        Bounds2di bounds2Df({-1, -2}, {2, 1});

        REQUIRE_FALSE(bounds2Df.contains(Vector2f(2, 2)));
    }

    SECTION("Bounds2di should contain Vector2i") {
        Bounds2di bounds2Df({-1, -2}, {2, 1});

        REQUIRE(bounds2Df.contains(Vector2i(0, 0)));
    }

    SECTION("Bounds2di should not contain Vector2i") {
        Bounds2di bounds2Df({-1, -2}, {2, 1});

        REQUIRE_FALSE(bounds2Df.contains(Vector2i(2, 2)));
    }
}

TEST_CASE("Bounds2d::diagonal") {
    SECTION("should return correct diagonal for Bounds2df") {
        Bounds2df bounds2Df({0, 0}, {2, 3});

        const Vector2f diagonal = bounds2Df.diagonal();

        REQUIRE(diagonal == Vector2f(2, 3));
    }

    SECTION("should return correct diagonal for Bounds2di") {
        Bounds2di bounds2Df({0, 0}, {2, 3});

        const Vector2i diagonal = bounds2Df.diagonal();

        REQUIRE(diagonal == Vector2i(2, 3));
    }
}

TEST_CASE("Bounds2d::area") {
    SECTION("should return correct area for Bounds2df consisting of one point") {
        Bounds2df bounds2df({1, 1}, {1, 1});

        const float area = bounds2df.area();

        REQUIRE(area == 0);
    }

    SECTION("should return correct area for Bounds2df") {
        Bounds2df bounds2df({1, 1}, {3, 3});

        const float area = bounds2df.area();

        REQUIRE(area == 4);
    }

    SECTION("should return correct area for Bounds2di consisting of one point") {
        Bounds2di bounds2di({1, 1}, {1, 1});

        const float area = bounds2di.area();

        REQUIRE(area == 0);
    }

    SECTION("should return correct area for Bounds2di") {
        Bounds2di bounds2di({1, 1}, {3, 3});

        const float area = bounds2di.area();

        REQUIRE(area == 4);
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

        REQUIRE(os.str() == "Bounds2df{min=Vector2{x=1,y=2},max=Vector2{x=3,y=4}}");
    }

    SECTION("should be formatable") {
        Bounds2df bounds2Df({1, 2}, {3, 4});

        REQUIRE(fmt::format("{}", bounds2Df) == "Bounds2df{min=Vector2{x=1,y=2},max=Vector2{x=3,y=4}}");
    }
}

TEST_CASE("Bounds2d::getWidth") {

    SECTION("float should be non-inclusive") {
        Bounds2df bounds({1, 1}, {2, 3});

        REQUIRE(bounds.getWidth() == 1);
    }

    SECTION("int should be non-inclusive") {
        Bounds2di bounds({1, 1}, {2, 3});

        REQUIRE(bounds.getWidth() == 2);
    }
}

TEST_CASE("Bounds2d::getHeight") {

    SECTION("float should be non-inclusive") {
        Bounds2df bounds({1, 1}, {2, 3});

        REQUIRE(bounds.getHeight() == 2);
    }

    SECTION("int should be non-inclusive") {
        Bounds2di bounds({1, 1}, {2, 3});

        REQUIRE(bounds.getHeight() == 3);
    }
}

}