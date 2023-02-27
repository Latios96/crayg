#include "sceneIO/SceneWriterFactory.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("TestSceneWriterFactory::createSceneWriter") {
    Scene scene;

    SECTION("should return SceneWriter for .usd") {
        auto reader = SceneWriterFactory::createSceneWriter("test.usd", scene);

        REQUIRE(reader != nullptr);
    }

    SECTION("should return SceneWriter for .usda") {
        auto reader = SceneWriterFactory::createSceneWriter("test.usda", scene);

        REQUIRE(reader != nullptr);
    }

    SECTION("should return SceneWriter for .usdc") {
        auto reader = SceneWriterFactory::createSceneWriter("test.usdc", scene);

        REQUIRE(reader != nullptr);
    }

    SECTION("should throw exception for unsupported extension") {
        REQUIRE_THROWS_AS(SceneWriterFactory::createSceneWriter("test.unkown", scene), std::runtime_error);
    }
}

}
