#include "crayg/imaging/lensio/textfile/LensFileTextFileReader.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("LensFileTextFileReader::readFileContent") {
    LensFileTextFileReader lensFileTextFileReader;

    SECTION("should read file with lens count correctly") {
        auto fileContent = GENERATE(R"(# a header comment
3
1 2 3 4
5 6 7 8)",
                                    R"(# a header comment
3 # comment after lens count
1 2 3 4
5 6 7 8)",
                                    R"(# a header comment
# a header comment
3
1 2 3 4
5 6 7 8
#9 10 11 12)",
                                    R"(# a header comment
# a header comment
1 2 3 4
5 6 7 8
#9 10 11 12)",
                                    R"(# a header comment
# a header comment
1   2   3   4
5   6   7   8
#9 10 11    12)");

        auto cameraLens = lensFileTextFileReader.readFileContent(fileContent);

        REQUIRE(cameraLens == CameraLens(CameraLensMetadata(),
                                         std::vector<LensSurface>({{0.1f, 0.2f, 3.f, 0.2f}, {0.5f, 0.6f, 7.f, 0.4f}})));
    }
}

}