#include "scene/camera/lensio/LensFileJsonWriter.h"
#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>

namespace crayg {

TEST_CASE("TestLensFileJsonWriter::writeFileContent") {

    SECTION("should write file content with name") {
        LensFileJsonWriter lensFileJsonWriter;
        CameraLens cameraLens("Canon 70-200", {{1, 2, 3, 4}, {5, 6, 7, 8}});

        auto fileContent = lensFileJsonWriter.writeFileContent(cameraLens);

        auto parsedJson = nlohmann::json::parse(fileContent);
        REQUIRE(parsedJson.size() == 3);
        REQUIRE(parsedJson["name"] == "Canon 70-200");
        REQUIRE(parsedJson["focalLength"] == Catch::Detail::Approx(40.38469314575195));
        REQUIRE(parsedJson["elements"].size() == 2);
        REQUIRE(parsedJson["elements"][0].size() == 4);
        REQUIRE(parsedJson["elements"][0]["curvatureRadius"] == Catch::Detail::Approx(10));
        REQUIRE(parsedJson["elements"][0]["thickness"] == Catch::Detail::Approx(20));
        REQUIRE(parsedJson["elements"][0]["ior"] == 3);
        REQUIRE(parsedJson["elements"][0]["apertureRadius"] == Catch::Detail::Approx(40));
    }
}

}