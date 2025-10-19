#include "crayg/scene/camera/realistic/lensio/json/LensFileJsonReader.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("LensFileJsonReader::readFileContent") {

    SECTION("should read file content successfully") {
        std::string content = R"(
{
   "name":"Canon 70-200",
   "surfaces":[
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

        REQUIRE(cameraLens ==
                CameraLens(CameraLensMetadata("Canon 70-200"), {{0.1f, 0.2f, 3.f, 0.4f}, {0.5f, 0.6f, 7.f, 0.8f}}));
    }
}

}