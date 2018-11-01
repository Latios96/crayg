//
// Created by Jan Honsbrok on 28.10.18.
//
#include <catch.hpp>
#include <utils/ToStringHelper.h>

TEST_CASE("ToStringHelper", "[ToStringHelper]") {
    ToStringHelper helper("TestClass");

    SECTION("emptyClass") {
        REQUIRE(helper.finish() == "TestClass{}");
    }

    SECTION("oneMember") {
        helper.addMember("myMember", 1);
        REQUIRE(helper.finish() == "TestClass{myMember=1}");
    }

    SECTION("twoMembers") {
        helper
        .addMember("myMember", 1)
        .addMember("myMember2", 2);
        REQUIRE(helper.finish() == "TestClass{myMember=1,myMember2=2}");
    }
}

