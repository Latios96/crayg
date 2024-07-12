#include "fixtures/CameraLensFixtures.h"
#include "scene/camera/realistic/lensio/extendedformat/LensFileExtendedFormatReader.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("LensFileExtendedFormatReader::readFileContent with success") {
    LensFileExtendedFormatReader lensFileExtendedFormatReader;

    SECTION("should parse valid extended lens file") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
Maximum F Number: 2.8
Patent: US 123
Description: An Example Lens
[Surfaces]
Radius  Thickness   IOR HousingRadius  Abbe-no Material        Geometry
1       2           3   4              5       SCHOTT_LAFN7    PLANAR
6       7           8   9              10      SCHOTT_K7       SPHERICAL
)";

        auto cameraLens = lensFileExtendedFormatReader.readFileContent(fileContent);

        REQUIRE(
            cameraLens ==
            CameraLens(CameraLensMetadata("A Zoom Lens", 0.46001232, 2.8, false, 1, 0, 42, "US 123", "An Example Lens"),
                       std::vector<LensSurface>(
                           {{0.1f, 0.2f, 3.f, 0.4f, 5, LensMaterial::createMaterialById(LensMaterialId::SCHOTT_LAFN7),
                             LensGeometry::PLANAR},
                            {0.6f, 0.7f, 8.f, 0.90000004f, 10,
                             LensMaterial::createMaterialById(LensMaterialId::SCHOTT_K7), LensGeometry::SPHERICAL}})));
    }

    SECTION("should parse extended lens file with minimal metadata") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Surfaces]
Radius  Thickness   IOR HousingRadius  Abbe-no Material        Geometry
1       2           3   4              5       SCHOTT_LAFN7    PLANAR
6       7           8   9              10      SCHOTT_K7       SPHERICAL
)";

        auto cameraLens = lensFileExtendedFormatReader.readFileContent(fileContent);

        REQUIRE(
            cameraLens ==
            CameraLens(CameraLensMetadata("A Zoom Lens"),
                       std::vector<LensSurface>(
                           {{0.1f, 0.2f, 3.f, 0.4f, 5, LensMaterial::createMaterialById(LensMaterialId::SCHOTT_LAFN7),
                             LensGeometry::PLANAR},
                            {0.6f, 0.7f, 8.f, 0.90000004f, 10,
                             LensMaterial::createMaterialById(LensMaterialId::SCHOTT_K7), LensGeometry::SPHERICAL}})));
    }
    SECTION("should ignore metadata that is calculated anyway") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
Focal Length: 50
Squeeze: 2
Maximum F Number: 2.8
Patent: US 123
Description: An Example Lens
[Surfaces]
Radius  Thickness   IOR HousingRadius  Abbe-no Material        Geometry
1       2           3   4              5       SCHOTT_LAFN7    PLANAR
6       7           8   9              10      SCHOTT_K7       SPHERICAL
)";

        auto cameraLens = lensFileExtendedFormatReader.readFileContent(fileContent);

        REQUIRE(
            cameraLens ==
            CameraLens(CameraLensMetadata("A Zoom Lens", 0.46001232, 2.8, false, 1, 0, 42, "US 123", "An Example Lens"),
                       std::vector<LensSurface>(
                           {{0.1f, 0.2f, 3.f, 0.4f, 5, LensMaterial::createMaterialById(LensMaterialId::SCHOTT_LAFN7),
                             LensGeometry::PLANAR},
                            {0.6f, 0.7f, 8.f, 0.90000004f, 10,
                             LensMaterial::createMaterialById(LensMaterialId::SCHOTT_K7), LensGeometry::SPHERICAL}})));
    }

    SECTION("should parse extended lens file with no surfaces header") {
        const std::string fileContent = R"(# a header comment
[Metadata]
name: A Zoom Lens
[Surfaces]
1       2           3   4              5       SCHOTT_LAFN7    PLANAR
6       7           8   9              10      SCHOTT_K7       SPHERICAL
)";

        auto cameraLens = lensFileExtendedFormatReader.readFileContent(fileContent);

        REQUIRE(
            cameraLens ==
            CameraLens(CameraLensMetadata("A Zoom Lens"),
                       std::vector<LensSurface>(
                           {{0.1f, 0.2f, 3.f, 0.4f, 5, LensMaterial::createMaterialById(LensMaterialId::SCHOTT_LAFN7),
                             LensGeometry::PLANAR},
                            {0.6f, 0.7f, 8.f, 0.90000004f, 10,
                             LensMaterial::createMaterialById(LensMaterialId::SCHOTT_K7), LensGeometry::SPHERICAL}})));
    }
}

TEST_CASE("LensFileExtendedFormatReader::readFileContent with failure") {
    LensFileExtendedFormatReader lensFileExtendedFormatReader;

    SECTION("should throw exception if lens name is missing") {
        const std::string fileContent = R"(# a header comment
[Metadata]
[Surfaces]
1       2           3   4              5       SCHOTT_LAFN7    PLANAR
6       7           8   9              10      SCHOTT_K7       SPHERICAL
)";

        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: [Metadata] section is missing 'name'"));
    }

    SECTION("should throw exception if surfaces section is missing") {
        const std::string fileContent = R"(# a header comment
[Metadata]
name: A Zoom Lens
)";

        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: [Surfaces] section is missing"));
    }

    SECTION("should throw exception if surfaces section is empty") {
        const std::string fileContent = R"(# a header comment
[Metadata]
name: A Zoom Lens
[Surfaces]
)";

        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: [Surfaces] section is empty"));
    }

    SECTION("should throw exception if an surfaces contains non-float radius") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Surfaces]
# comment
Radius  Thickness   IOR HousingRadius  Abbe-no Material Geometry
# comment
1     2           3   4              5       SCHOTT_LAFN7    PLANAR
# comment
abc   7           8   9              10      SCHOTT_K7       SPHERICAL
)";
        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 11: Value 'abc' for Radius is not a float"));
    }

    SECTION("should throw exception if an surfaces contains non-float thickness") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Surfaces]
# comment
Radius  Thickness   IOR HousingRadius  Abbe-no Material      Geometry
# comment
1     2           3   4              5       SCHOTT_LAFN7    PLANAR
# comment
1     abc         8   9              10      SCHOTT_K7       SPHERICAL
)";
        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 11: Value 'abc' for Thickness is not a float"));
    }

    SECTION("should throw exception if an surfaces contains non-float IOR") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Surfaces]
# comment
Radius  Thickness   IOR HousingRadius  Abbe-no Material      Geometry
# comment
1     2           3   4              5       SCHOTT_LAFN7    PLANAR
# comment
1     2           abc 9              10      SCHOTT_K7       SPHERICAL
)";
        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 11: Value 'abc' for IOR is not a float"));
    }

    SECTION("should throw exception if an surface contains non-float housing radius") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Surfaces]
# comment
Radius  Thickness   IOR HousingRadius  Abbe-no Material      Geometry
# comment
1     2           3   4              5       SCHOTT_LAFN7    PLANAR
# comment
1     2           3   abc            10      SCHOTT_K7       SPHERICAL
)";
        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 11: Value 'abc' for Housing Radius is not a float"));
    }

    SECTION("should throw exception if an surface contains non-float abbe no") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Surfaces]
# comment
Radius  Thickness   IOR HousingRadius  Abbe-no Material        Geometry
# comment
1     2           3     4              5       SCHOTT_LAFN7    PLANAR
# comment
1     2           3     4              abc     SCHOTT_K7       SPHERICAL
)";
        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 11: Value 'abc' for Abbe-No is not a float"));
    }

    SECTION("should throw exception if an surface contains invalid material") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Surfaces]
# comment
Radius  Thickness   IOR HousingRadius  Abbe-no Material        Geometry
# comment
1     2           3     4              5       SCHOTT_LAFN7    PLANAR
# comment
1     2           3     4              5       foo             SPHERICAL
)";
        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 11: 'foo' is an unsupported material value"));
    }

    SECTION("should throw exception if an surface contains invalid lens geometry") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Surfaces]
# comment
Radius  Thickness   IOR HousingRadius  Abbe-no Material        Geometry
# comment
1     2           3     4              5       SCHOTT_LAFN7    PLANAR
# comment
1     2           3     4              5       SCHOTT_F2    CUBICAL
)";
        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 11: 'cubical' is an unsupported LensGeometry"));
    }

    SECTION("should throw because surface line is empty") {
        const std::string fileContent = R"(# a header comment
[Metadata]
# comment
name: A Zoom Lens
[Surfaces]
Radius  Thickness   IOR HousingRadius  Abbe-no Material        Geometry
1       2           3   4              5       SCHOTT_LAFN7    PLANAR
1
6       7           8   9              10      SCHOTT_K7       SPHERICAL
)";

        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 8: Value '' for Thickness is not a float"));
    }

    SECTION("should parse valid extended lens file with aspheric lens") {
        const std::string fileContent = R"(# a header comment
[Metadata]
Name: Aspheric Lens
Focal Length: 54.2
Maximum F Number: 1.08
Squeeze: 1
Surface Count: 2
[Surfaces]
Radius Thickness IOR  Housing-Radius Abbe-No Material     Geometry   
24     21        1    50             25      SCHOTT_N_SF6 ASPHERICAL 
24     21        1    50             25      SCHOTT_N_SF6 ASPHERICAL 
0      18        1    50             0       AIR          PLANAR     
[Aspheric Coefficients]
0: k=-1.103426 a2=0 a4=4.605084e-06 a6=4.544628e-10 a8=-2.257169e-12 a10=5.828326e-16 a12=0 a14=0
1: k=1      a2=0 a4=4.605084e-06      a6=4.544628e-10    a8=-2.257169e-12 a10=5.828326e-16 a12=0 a14=0
)";
        auto cameraLens = lensFileExtendedFormatReader.readFileContent(fileContent);
        for (auto &surface : cameraLens.surfaces) {
            surface.center = 0;
        }
        REQUIRE(cameraLens.metadata ==
                CameraLensMetadata("Aspheric Lens", 5.3817177, 1.08, false, 1, 3, 21.728516, "", ""));
        REQUIRE(cameraLens.surfaces[0] ==
                LensSurface({2.4, 2.1000001, 1., 5, 25, LensMaterial::createMaterialById(LensMaterialId::SCHOTT_N_SF6),
                             LensGeometry::ASPHERICAL, 0}));
        REQUIRE(cameraLens.surfaces[1] ==
                LensSurface({2.4, 2.1000001, 1., 5, 25, LensMaterial::createMaterialById(LensMaterialId::SCHOTT_N_SF6),
                             LensGeometry::ASPHERICAL, 1}));
        REQUIRE(cameraLens.surfaces[2] ==
                LensSurface({0, 1.8000001, 1, 5, 0, LensMaterial::createMaterialById(LensMaterialId::AIR),
                             LensGeometry::PLANAR}));

        REQUIRE(cameraLens.asphericCoefficients ==
                std::vector<AsphericCoefficients>(
                    {{-1.103426, 0, 4.605084E-06, 4.544628E-10, -2.257169E-12, 5.828326E-16, 0, 0},
                     {1, 0, 4.605084E-06, 4.544628E-10, -2.257169E-12, 5.828326E-16, 0, 0}}));
    }

    SECTION("should default unspecified coefficients to 0") {
        const std::string fileContent = R"(# a header comment
[Metadata]
Name: Aspheric Lens

[Surfaces]
Radius Thickness IOR  Housing-Radius Abbe-No Material     Geometry   
24     21        1    50             25      SCHOTT_N_SF6 ASPHERICAL
[Aspheric Coefficients]
0: k=0 a4=1  a6=2 a8=3
)";
        auto cameraLens = lensFileExtendedFormatReader.readFileContent(fileContent);

        REQUIRE(cameraLens.asphericCoefficients == std::vector<AsphericCoefficients>({{0, 0, 1, 2, 3, 0, 0, 0}}));
    }

    SECTION("should throw error because aspheric coefficient line contains too many :") {
        const std::string fileContent = R"(# a header comment
[Metadata]
Name: Aspheric Lens
[Surfaces]
Radius Thickness IOR  Housing-Radius Abbe-No Material     Geometry   
24     21        1    50             25      SCHOTT_N_SF6 ASPHERICAL 

[Aspheric Coefficients]
0::
)";

        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 9: '0::' is an invalid aspheric coefficients line"));
    }

    SECTION("should throw error because aspheric coefficient line contains too many :") {
        const std::string fileContent = R"(# a header comment
[Metadata]
Name: Aspheric Lens
[Surfaces]
Radius Thickness IOR  Housing-Radius Abbe-No Material     Geometry   
24     21        1    50             25      SCHOTT_N_SF6 ASPHERICAL 

[Aspheric Coefficients]
0
)";

        REQUIRE_THROWS_WITH(
            lensFileExtendedFormatReader.readFileContent(fileContent),
            Catch::Equals("Invalid lens file: Line 9: '0' is an incomplete aspheric coefficients line"));
    }

    SECTION("should throw error because lens index is invalid") {
        const std::string fileContent = R"(# a header comment
[Metadata]
Name: Aspheric Lens
[Surfaces]
Radius Thickness IOR  Housing-Radius Abbe-No Material     Geometry   
24     21        1    50             25      SCHOTT_N_SF6 ASPHERICAL 

[Aspheric Coefficients]
10: k=1 a2=0 a4=4.605084e-06 a6=4.544628e-10 a8=-2.257169e-12 a10=5.828326e-16 a12=0 a14=0
)";

        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 9: 10 is an invalid lens index, valid is [0-1]"));
    }

    SECTION("should throw error because lens with specidied coefficients is not aspheric") {
        const std::string fileContent = R"(# a header comment
[Metadata]
Name: Aspheric Lens
[Surfaces]
Radius Thickness IOR  Housing-Radius Abbe-No Material     Geometry   
24     21        1    50             25      SCHOTT_N_SF6 SPHERICAL 

[Aspheric Coefficients]
0: k=1 a2=0 a4=4.605084e-06 a6=4.544628e-10 a8=-2.257169e-12 a10=5.828326e-16 a12=0 a14=0
)";

        REQUIRE_THROWS_WITH(
            lensFileExtendedFormatReader.readFileContent(fileContent),
            Catch::Equals("Invalid lens file: Line 9: lens surface 0 is not an aspheric lens, it's SPHERICAL"));
    }

    SECTION("should throw error because coefficient format is invalid") {
        const std::string fileContent = R"(# a header comment
[Metadata]
Name: Aspheric Lens
[Surfaces]
Radius Thickness IOR  Housing-Radius Abbe-No Material     Geometry   
24     21        1    50             25      SCHOTT_N_SF6 ASPHERICAL 

[Aspheric Coefficients]
0: k1 a2=0 a4=4.605084e-06 a6=4.544628e-10 a8=-2.257169e-12 a10=5.828326e-16 a12=0 a14=0
)";

        REQUIRE_THROWS_WITH(
            lensFileExtendedFormatReader.readFileContent(fileContent),
            Catch::Equals("Invalid lens file: Line 9: 'k1' is an invalid coefficient format, only k=v is allowed"));
    }

    SECTION("should throw error because coefficient name is invalid") {
        const std::string fileContent = R"(# a header comment
[Metadata]
Name: Aspheric Lens
[Surfaces]
Radius Thickness IOR  Housing-Radius Abbe-No Material     Geometry   
24     21        1    50             25      SCHOTT_N_SF6 ASPHERICAL 

[Aspheric Coefficients]
0: b=1 a2=0 a4=4.605084e-06 a6=4.544628e-10 a8=-2.257169e-12 a10=5.828326e-16 a12=0 a14=0
)";

        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: Line 9: 'b' is an invalid coefficient name"));
    }

    SECTION("should throw error because no coefficients for aspheric lens") {
        const std::string fileContent = R"(# a header comment
[Metadata]
Name: Aspheric Lens
[Surfaces]
Radius Thickness IOR  Housing-Radius Abbe-No Material     Geometry   
24     21        1    50             25      SCHOTT_N_SF6 ASPHERICAL 

[Aspheric Coefficients]
)";

        REQUIRE_THROWS_WITH(lensFileExtendedFormatReader.readFileContent(fileContent),
                            Catch::Equals("Invalid lens file: surface 0 is aspheric, but has no coefficients"));
    }
}

}