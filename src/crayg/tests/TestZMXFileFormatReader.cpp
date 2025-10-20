#include "crayg/imaging/lensio/zmx/ZMXFileFormatReader.h"

#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("ZMXFileFormatReader::read()") {
    ZMXFileFormatReader reader;

    SECTION("should read a spherical lens successfully") {
        const std::string content = R"(
UNIT MM X W X CM MR CPMM
SURF 15
  TYPE STANDARD
  CURV 7.969685042737270600E-002 0 0 0 0 ""
  HIDE 0 0 0 0 0 0 0 0 0 0
  MIRR 2 0
  SLAB 4
  DISZ 1
  GLAS LAK10 0 0 1.5 4.0E+1 0 0 0 0 0 0
  DIAM 4.5 1 0 0 1 ""
  POPS 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0
  FLAP 0 4.5 0
)";

        CameraLens cameraLens = reader.readFileContent(content);

        for (auto &surf : cameraLens.surfaces) {
            surf.center = 0;
        }

        REQUIRE(cameraLens.surfaces ==
                std::vector<LensSurface>(
                    {{1.2547548f, 0.1f, 1.72003f, 0.45000002f, 50.62,
                      LensMaterial::createMaterialById(LensMaterialId::SCHOTT_N_LAK10), LensGeometry::SPHERICAL}}));
    }

    SECTION("should read multiple lenses successfully") {
        const std::string content = R"(
UNIT MM X W X CM MR CPMM
SURF 15
  TYPE STANDARD
  CURV 7.969685042737270600E-002 0 0 0 0 ""
  HIDE 0 0 0 0 0 0 0 0 0 0
  MIRR 2 0
  SLAB 4
  DISZ 1
  GLAS LAK10 0 0 1.5 4.0E+1 0 0 0 0 0 0
  DIAM 4.5 1 0 0 1 ""
  POPS 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0
  FLAP 0 4.5 0
SURF 15
  TYPE STANDARD
  CURV 7.969685042737270600E-002 0 0 0 0 ""
  HIDE 0 0 0 0 0 0 0 0 0 0
  MIRR 2 0
  SLAB 4
  DISZ 1
  GLAS LAK10 0 0 1.5 4.0E+1 0 0 0 0 0 0
  DIAM 4.5 1 0 0 1 ""
  POPS 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0
  FLAP 0 4.5 0
)";

        CameraLens cameraLens = reader.readFileContent(content);

        for (auto &surf : cameraLens.surfaces) {
            surf.center = 0;
        }

        REQUIRE(cameraLens.surfaces ==
                std::vector<LensSurface>(
                    {{1.2547548f, 0.1f, 1.72003f, 0.45000002f, 50.62,
                      LensMaterial::createMaterialById(LensMaterialId::SCHOTT_N_LAK10), LensGeometry::SPHERICAL},
                     {1.2547548f, 0.1f, 1.72003f, 0.45000002f, 50.62,
                      LensMaterial::createMaterialById(LensMaterialId::SCHOTT_N_LAK10), LensGeometry::SPHERICAL}}));
    }

    SECTION("should remove object and image plane") {
        const std::string content = R"(
UNIT MM X W X CM MR CPMM
SURF 0
  TYPE STANDARD
  CURV 0.0 0 0 0 0 ""
  HIDE 0 0 0 0 0 0 0 0 0 0
  MIRR 2 0
  SLAB 1
  DISZ 10
  DIAM 0 0 0 0 1 ""
  POPS 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0
SURF 15
  TYPE STANDARD
  CURV 7.969685042737270600E-002 0 0 0 0 ""
  HIDE 0 0 0 0 0 0 0 0 0 0
  MIRR 2 0
  SLAB 4
  DISZ 1
  GLAS LAK10 0 0 1.5 4.0E+1 0 0 0 0 0 0
  DIAM 4.5 1 0 0 1 ""
  POPS 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0
  FLAP 0 4.5 0
SURF 15
  TYPE STANDARD
  CURV 7.969685042737270600E-002 0 0 0 0 ""
  HIDE 0 0 0 0 0 0 0 0 0 0
  MIRR 2 0
  SLAB 4
  DISZ 1
  GLAS LAK10 0 0 1.5 4.0E+1 0 0 0 0 0 0
  DIAM 4.5 1 0 0 1 ""
  POPS 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0
  FLAP 0 4.5 0
SURF 16
  TYPE STANDARD
  CURV 0.0 0 0 0 0 ""
  HIDE 0 0 0 0 0 0 0 0 0 0
  MIRR 2 0
  SLAB 3
  DISZ 0
  DIAM 1.583674494711E+1 0 0 0 1 ""
  POPS 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0
)";

        CameraLens cameraLens = reader.readFileContent(content);

        for (auto &surf : cameraLens.surfaces) {
            surf.center = 0;
        }

        REQUIRE(cameraLens.surfaces ==
                std::vector<LensSurface>(
                    {{1.2547548f, 0.1f, 1.72003f, 0.45000002f, 50.62,
                      LensMaterial::createMaterialById(LensMaterialId::SCHOTT_N_LAK10), LensGeometry::SPHERICAL},
                     {1.2547548f, 0.1f, 1.72003f, 0.45000002f, 50.62,
                      LensMaterial::createMaterialById(LensMaterialId::SCHOTT_N_LAK10), LensGeometry::SPHERICAL}}));
    }

    SECTION("should respect UNIT line") {
        const std::string content = R"(
UNIT INCH X W X CM MR CPMM
SURF 15
  TYPE STANDARD
  CURV 7.969685042737270600E-002 0 0 0 0 ""
  HIDE 0 0 0 0 0 0 0 0 0 0
  MIRR 2 0
  SLAB 4
  DISZ 1
  GLAS LAK10 0 0 1.5 4.0E+1 0 0 0 0 0 0
  DIAM 4.5 1 0 0 1 ""
  POPS 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0
  FLAP 0 4.5 0
)";

        CameraLens cameraLens = reader.readFileContent(content);

        for (auto &surf : cameraLens.surfaces) {
            surf.center = 0;
        }

        REQUIRE(cameraLens.surfaces ==
                std::vector<LensSurface>(
                    {{31.87077f, 2.54f, 1.72003f, 11.43f, 50.62,
                      LensMaterial::createMaterialById(LensMaterialId::SCHOTT_N_LAK10), LensGeometry::SPHERICAL}}));
    }

    SECTION("should throw for invalid UNIT line") {
        const std::string content = R"(
UNIT
)";

        REQUIRE_THROWS_WITH(
            reader.readFileContent(content),
            Catch::Equals("Invalid lens file: Line 2: Invalid UNIT line, expected at least 2 values, got 1"));
    }

    SECTION("should throw for invalid CURV line") {
        const std::string content = R"(
UNIT MM X W X CM MR CPMM
SURF 15
  TYPE STANDARD
  CURV
  HIDE 0 0 0 0 0 0 0 0 0 0
  MIRR 2 0
  SLAB 4
  DISZ 1
  GLAS LAK10 0 0 1.5 4.0E+1 0 0 0 0 0 0
  DIAM 4.5 1 0 0 1 ""
  POPS 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0
  FLAP 0 4.5 0
)";

        REQUIRE_THROWS_WITH(
            reader.readFileContent(content),
            Catch::Equals("Invalid lens file: Line 5: Invalid CURV line, expected at least 2 values, got 1"));
    }

    SECTION("should throw for invalid DIAM line") {
        const std::string content = R"(
UNIT MM X W X CM MR CPMM
SURF 15
  TYPE STANDARD
  CURV 7.969685042737270600E-002 0 0 0 0 ""
  HIDE 0 0 0 0 0 0 0 0 0 0
  MIRR 2 0
  SLAB 4
  DISZ 1
  GLAS LAK10 0 0 1.5 4.0E+1 0 0 0 0 0 0
  DIAM
  POPS 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0
  FLAP 0 4.5 0
)";

        REQUIRE_THROWS_WITH(
            reader.readFileContent(content),
            Catch::Equals("Invalid lens file: Line 11: Invalid DIAM line, expected at least 2 values, got 1"));
    }

    SECTION("should throw for invalid DISZ line") {
        const std::string content = R"(
UNIT MM X W X CM MR CPMM
SURF 15
  TYPE STANDARD
  CURV 7.969685042737270600E-002 0 0 0 0 ""
  HIDE 0 0 0 0 0 0 0 0 0 0
  MIRR 2 0
  SLAB 4
  DISZ
  GLAS LAK10 0 0 1.5 4.0E+1 0 0 0 0 0 0
  DIAM 4.5 1 0 0 1 ""
  POPS 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0
  FLAP 0 4.5 0
)";

        REQUIRE_THROWS_WITH(
            reader.readFileContent(content),
            Catch::Equals("Invalid lens file: Line 9: Invalid DISZ line, expected at least 2 values, got 1"));
    }

    SECTION("should throw for invalid GLAS line") {
        const std::string content = R"(
UNIT MM X W X CM MR CPMM
SURF 15
  TYPE STANDARD
  CURV 7.969685042737270600E-002 0 0 0 0 ""
  HIDE 0 0 0 0 0 0 0 0 0 0
  MIRR 2 0
  SLAB 4
  DISZ 1
  GLAS
  DIAM 4.5 1 0 0 1 ""
  POPS 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0
  FLAP 0 4.5 0
)";

        REQUIRE_THROWS_WITH(
            reader.readFileContent(content),
            Catch::Equals("Invalid lens file: Line 10: Invalid GLAS line, expected at least 6 values, got 1"));
    }

    SECTION("should throw for incomplete last surface with missing DIAM") {
        const std::string content = R"(
UNIT MM X W X CM MR CPMM
SURF 15
  TYPE STANDARD
  CURV 7.969685042737270600E-002 0 0 0 0 ""
  HIDE 0 0 0 0 0 0 0 0 0 0
  MIRR 2 0
  SLAB 4
  DISZ 1
  GLAS LAK10 0 0 1.5 4.0E+1 0 0 0 0 0 0
  DIAM 4.5 1 0 0 1 ""
  POPS 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0
  FLAP 0 4.5 0
UNIT MM X W X CM MR CPMM
SURF 15
  TYPE STANDARD
  CURV 7.969685042737270600E-002 0 0 0 0 ""
  HIDE 0 0 0 0 0 0 0 0 0 0
  MIRR 2 0
  SLAB 4
  DISZ 1
  POPS 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0
  FLAP 0 4.5 0
)";

        REQUIRE_THROWS_WITH(
            reader.readFileContent(content),
            Catch::Equals("Invalid lens file: Line 15: Defined surface is incomplete, missing terms [DIAM]"));
    }

    SECTION("should throw for no surfaces") {
        const std::string content = R"(
UNIT MM X W X CM MR CPMM
)";

        REQUIRE_THROWS_WITH(reader.readFileContent(content),
                            Catch::Equals("Invalid lens file: No Surfaces are defined"));
    }
}
}