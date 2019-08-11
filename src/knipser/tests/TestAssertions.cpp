//
// Created by Jan Honsbrok on 2019-08-11.
//
#include <catch2/catch.hpp>
#include <KnipserAssertions.h>

TEST_CASE("BasicAssertion") {

    SECTION("create basic assertion") {
        BasicAssertion basicAssertion(__FILE__, __LINE__);
    }

    SECTION("createMessage") {
        BasicAssertion basicAssertion("TestBasicAssertion.cpp", 10);
        REQUIRE(basicAssertion.createMessage("test") == "TestBasicAssertion.cpp:10: Failure:\ntest");
    }

    SECTION("doAssertThrows") {
        BasicAssertion basicAssertion("TestBasicAssertion.cpp", 10);
        REQUIRE_THROWS_AS(basicAssertion.doAssert(false, "message"), KnipserException);
    }

    SECTION("doAssertThrowsNot") {
        BasicAssertion basicAssertion("TestBasicAssertion.cpp", 10);
        REQUIRE_NOTHROW(basicAssertion.doAssert(true, "message"));
    }
}


class ImageOutputExistsAssertionUnderTest : public ImageOutputExistsAssertion {
public:
    ImageOutputExistsAssertionUnderTest(bool doesExists)
            : ImageOutputExistsAssertion("TestBasicAssertion.cpp", 10), doesExists(doesExists) {}

protected:
    bool exists(const boost::filesystem::path &path) const override {
        return doesExists;
    }

private:
    bool doesExists;
};

TEST_CASE("ImageOutputExistsAssertion") {
    TestContext testContext("demo");

    SECTION("imageOutputNotSetShouldThrow") {
        ImageOutputExistsAssertion assertion("TestBasicAssertion.cpp", 10);
        REQUIRE_THROWS_AS(assertion.doAssert(testContext), KnipserException);
    }

    SECTION("imageOutputNotExistsShouldThrow") {
        ImageOutputExistsAssertionUnderTest assertion(false);
        testContext.setImageOutputName("test.exr");

        REQUIRE_THROWS_AS(assertion.doAssert(testContext), KnipserException);
    }

    SECTION("imageOutputExistsShouldNotThrow") {
        ImageOutputExistsAssertionUnderTest assertion(true);
        testContext.setImageOutputName("test.exr");
        assertion.doAssert(testContext);
    }
}

