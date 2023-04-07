#include "scene/camera/lensio/LensFileJsonReader.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("LensFileJsonReader::readFileContent") {

    SECTION("should read file content successfully") {
        std::string content = R"(
{
   "name":"Canon 70-200",
   "elements":[
      {
         "curvatureRadius":1,
         "thickness":2,
         "ior":3,
         "apertureRadius":4
      },
      {
         "curvatureRadius":5,
         "thickness":6,
         "ior":7,
         "apertureRadius":8
      }
   ]
}
)";
        LensFileJsonReader lensFileJsonReader;

        auto cameraLens = lensFileJsonReader.readFileContent(content);

        REQUIRE(cameraLens == CameraLens("Canon 70-200", {{0.1, 0.2, 3, 0.4}, {0.5, 0.6, 7, 0.8}}));
    }
}

}