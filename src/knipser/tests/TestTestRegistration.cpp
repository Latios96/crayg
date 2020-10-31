//
// Created by jan on 03/08/2019.
//
#include <catch2/catch.hpp>
#include "TestRegistry.h"

std::vector<KnipserTest> renderTests() {
    return {KnipserTest("test1", [](TestContext &context) {

    })};
}
std::vector<KnipserTest> writeImageTests() {
    return {KnipserTest("test2", [](TestContext &context) {

    })};
}
TEST_CASE("testsShouldBeRegisteredByCallable") {
    TestRegistry testRegistry;
    testRegistry
        .registerTests(renderTests())
        .registerTests(writeImageTests());

    REQUIRE(testRegistry.getTests().size() == 2);
    REQUIRE(testRegistry.getTests()[0].name == "test1");
    REQUIRE(testRegistry.getTests()[1].name == "test2");
}
