//
// Created by Jan Honsbrok on 2019-08-11.
//
#include <catch2/catch.hpp>
#include <KnipserAssertions.h>

TEST_CASE("create BasicAssertion"){

    BasicAssertion basicAssertion(__FILE__, __LINE__);

}
TEST_CASE("BasicAssertion create message"){

    BasicAssertion basicAssertion("TestBasicAssertion.cpp", 10);
    REQUIRE(basicAssertion.createMessage("test") == "TestBasicAssertion.cpp:10: Failure:\ntest");

}

