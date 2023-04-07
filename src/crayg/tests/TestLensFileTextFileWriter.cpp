#include "scene/camera/lensio/LensFileTextFileWriter.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("TestLensFileTextFileWriter::writeFileContent") {

    SECTION("should write file content with name") {
        LensFileTextFileWriter lensFileTextFileWriter;
        CameraLens cameraLens("Canon 70-200", {{1, 2, 3, 4}, {5, 6, 7, 8}});

        auto fileContent = lensFileTextFileWriter.writeFileContent(cameraLens);

        REQUIRE(fileContent == R"(# Canon 70-200
2
10.00000 20.00000 3.00000 40.00000
50.00000 60.00000 7.00000 80.00000
)");
    }

    SECTION("should not write name if name is empty") {
        LensFileTextFileWriter lensFileTextFileWriter;
        CameraLens cameraLens("", {{1, 2, 3, 4}, {5, 6, 7, 8}});

        auto fileContent = lensFileTextFileWriter.writeFileContent(cameraLens);

        std::string expected = R"(2
10.00000 20.00000 3.00000 40.00000
50.00000 60.00000 7.00000 80.00000
)";
        REQUIRE(fileContent == expected);
    }
}

}