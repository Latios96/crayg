//
// Created by jan on 03/08/2019.
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "TestRegistry.h"

KNIPSER_REGISTER_TEST(threeSpheres, [](const TestContext &context){

});

KNIPSER_REGISTER_TEST(singleSphere, [](const TestContext &context){

});

TEST_CASE("testsShouldBeRegistered"){
    REQUIRE(TestRegistry::getInstance()->getTests().size() == 2);
    REQUIRE(TestRegistry::getInstance()->getTests()[0].name == "threeSpheres");
    REQUIRE(TestRegistry::getInstance()->getTests()[1].name == "singleSphere");
}

