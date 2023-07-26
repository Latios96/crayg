#include "scene/camera/lensio/LensFileExtendedFormatReader.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("LensFileExtendedFormatReader::readFileContent with success") {
    LensFileExtendedFormatReader lensFileExtendedFormatReader;

    SECTION("should parse valid extended lens file") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Elements]
Radius  Thickness   IOR HousingRadius  Abbe-no Material Geometry
1       2           3   4              5       LAFN7    PLANAR
6       7           8   9              10      K7       SPHERICAL
)";

        auto cameraLens = lensFileExtendedFormatReader.readFileContent(fileContent);

        REQUIRE(cameraLens ==
                CameraLens("A Zoom Lens",
                           std::vector<LensElement>(
                               {{0.1f, 0.2f, 3.f, 0.4f, 5, LensMaterial::LAFN7, LensGeometry::PLANAR},
                                {0.6f, 0.7f, 8.f, 0.90000004f, 10, LensMaterial::K7, LensGeometry::SPHERICAL}})));
    }

    SECTION("should parse extended lens file with minimal metadata") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Elements]
Radius  Thickness   IOR HousingRadius  Abbe-no Material Geometry
1       2           3   4              5       LAFN7    PLANAR
6       7           8   9              10      K7       SPHERICAL
)";

        auto cameraLens = lensFileExtendedFormatReader.readFileContent(fileContent);

        REQUIRE(cameraLens ==
                CameraLens("A Zoom Lens",
                           std::vector<LensElement>(
                               {{0.1f, 0.2f, 3.f, 0.4f, 5, LensMaterial::LAFN7, LensGeometry::PLANAR},
                                {0.6f, 0.7f, 8.f, 0.90000004f, 10, LensMaterial::K7, LensGeometry::SPHERICAL}})));
    }

    SECTION("should parse extended lens file with no elements header") {
        const std::string fileContent = R"(# a header comment
[Metadata]
name: A Zoom Lens
[Elements]
1       2           3   4              5       LAFN7    PLANAR
6       7           8   9              10      K7       SPHERICAL
)";

        auto cameraLens = lensFileExtendedFormatReader.readFileContent(fileContent);

        REQUIRE(cameraLens ==
                CameraLens("A Zoom Lens",
                           std::vector<LensElement>(
                               {{0.1f, 0.2f, 3.f, 0.4f, 5, LensMaterial::LAFN7, LensGeometry::PLANAR},
                                {0.6f, 0.7f, 8.f, 0.90000004f, 10, LensMaterial::K7, LensGeometry::SPHERICAL}})));
    }
}

TEST_CASE("LensFileExtendedFormatReader::readFileContent with failure") {
    LensFileExtendedFormatReader lensFileExtendedFormatReader;

    SECTION("should throw exception if lens name is missing") {
        const std::string fileContent = R"(# a header comment
[Metadata]
[Elements]
1       2           3   4              5       LAFN7    PLANAR
6       7           8   9              10      K7       SPHERICAL
)";

        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: [Metadata] section is missing 'name'"));
    }

    SECTION("should throw exception if elements section is missing") {
        const std::string fileContent = R"(# a header comment
[Metadata]
name: A Zoom Lens
)";

        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: [Elements] section is missing"));
    }

    SECTION("should throw exception if elements section is empty") {
        const std::string fileContent = R"(# a header comment
[Metadata]
name: A Zoom Lens
[Elements]
)";

        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: [Elements] section is empty"));
    }

    SECTION("should throw exception if an element contains non-float radius") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Elements]
# comment
Radius  Thickness   IOR HousingRadius  Abbe-no Material Geometry
# comment
1     2           3   4              5       LAFN7    PLANAR
# comment
abc   7           8   9              10      K7       SPHERICAL
)";
        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 10: Value 'abc' for Radius is not a float"));
    }

    SECTION("should throw exception if an element contains non-float thickness") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Elements]
# comment
Radius  Thickness   IOR HousingRadius  Abbe-no Material Geometry
# comment
1     2           3   4              5       LAFN7    PLANAR
# comment
1     abc         8   9              10      K7       SPHERICAL
)";
        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 10: Value 'abc' for Thickness is not a float"));
    }

    SECTION("should throw exception if an element contains non-float IOR") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Elements]
# comment
Radius  Thickness   IOR HousingRadius  Abbe-no Material Geometry
# comment
1     2           3   4              5       LAFN7    PLANAR
# comment
1     2           abc 9              10      K7       SPHERICAL
)";
        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 10: Value 'abc' for IOR is not a float"));
    }

    SECTION("should throw exception if an element contains non-float housing radius") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Elements]
# comment
Radius  Thickness   IOR HousingRadius  Abbe-no Material Geometry
# comment
1     2           3   4              5       LAFN7    PLANAR
# comment
1     2           3   abc            10      K7       SPHERICAL
)";
        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 10: Value 'abc' for Housing Radius is not a float"));
    }

    SECTION("should throw exception if an element contains non-float abbe no") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Elements]
# comment
Radius  Thickness   IOR HousingRadius  Abbe-no Material Geometry
# comment
1     2           3     4              5       LAFN7    PLANAR
# comment
1     2           3     4              abc     K7       SPHERICAL
)";
        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 10: Value 'abc' for Abbe-No is not a float"));
    }

    SECTION("should throw exception if an element contains invalid material") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Elements]
# comment
Radius  Thickness   IOR HousingRadius  Abbe-no Material Geometry
# comment
1     2           3     4              5       LAFN7    PLANAR
# comment
1     2           3     4              5       foo      SPHERICAL
)";
        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 10: 'foo' is an unsupported material value"));
    }

    SECTION("should throw exception if an element contains invalid lens geometry") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Elements]
# comment
Radius  Thickness   IOR HousingRadius  Abbe-no Material Geometry
# comment
1     2           3     4              5       LAFN7    PLANAR
# comment
1     2           3     4              5       LAFN7    CUBICAL
)";
        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 10: 'cubical' is an unsupported LensGeometry"));
    }

    SECTION("should throw because element line is empty") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Elements]
Radius  Thickness   IOR HousingRadius  Abbe-no Material Geometry
1       2           3   4              5       LAFN7    PLANAR
1
6       7           8   9              10      K7       SPHERICAL
)";

        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 7: Value '' for Thickness is not a float"));
    }
}

}