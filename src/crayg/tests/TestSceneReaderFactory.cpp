//
// Created by Jan on 19.05.2022.
//
#include <catch2/catch.hpp>
#include "sceneIO/SceneReaderFactory.h"

namespace crayg {

TEST_CASE("TestSceneReaderFactory/createSceneWriter") {
    Scene scene;
    SECTION("should return SceneReader for .json") {
        auto reader = SceneReaderFactory::createSceneWriter("test.json", scene);

        REQUIRE(reader != nullptr);
    }

    SECTION("should return SceneReader for .usd") {
        auto reader = SceneReaderFactory::createSceneWriter("test.usd", scene);

        REQUIRE(reader != nullptr);
    }

    SECTION("should throw exception for unsupported extension") {
        REQUIRE_THROWS_AS(SceneReaderFactory::createSceneWriter("test.unkown", scene), std::runtime_error);
    }
}

}
