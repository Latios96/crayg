#include "utils/ValueMapper.h"
#include <catch2/catch.hpp>

namespace crayg {

namespace testvaluemapper {

enum class LeftEnum { LEFT_0, LEFT_1, LEFT_2, LEFT_3 };

enum class RightEnum { RIGHT_0, RIGHT_1, RIGHT_2, RIGHT_3 };

ValueMapper<LeftEnum, RightEnum> mapper({{LeftEnum::LEFT_0, RightEnum::RIGHT_0},
                                         {LeftEnum::LEFT_1, RightEnum::RIGHT_1},
                                         {LeftEnum::LEFT_2, RightEnum::RIGHT_2}});

TEST_CASE("ValueMapper::mapFromLeft") {

    SECTION("should find value") {
        REQUIRE(mapper.mapFromLeft(LeftEnum::LEFT_0) == RightEnum::RIGHT_0);
        REQUIRE(mapper.mapFromLeft(LeftEnum::LEFT_1) == RightEnum::RIGHT_1);
        REQUIRE(mapper.mapFromLeft(LeftEnum::LEFT_2) == RightEnum::RIGHT_2);
    }

    SECTION("should not find value") {
        REQUIRE_FALSE(mapper.mapFromLeft(LeftEnum::LEFT_3).has_value());
    }
}

TEST_CASE("ValueMapper::mapFromRight") {

    SECTION("should find value") {
        REQUIRE(mapper.mapFromRight(RightEnum::RIGHT_0) == LeftEnum::LEFT_0);
        REQUIRE(mapper.mapFromRight(RightEnum::RIGHT_1) == LeftEnum::LEFT_1);
        REQUIRE(mapper.mapFromRight(RightEnum::RIGHT_2) == LeftEnum::LEFT_2);
    }

    SECTION("should not find value") {
        REQUIRE_FALSE(mapper.mapFromRight(RightEnum::RIGHT_3).has_value());
    }
}

}

}