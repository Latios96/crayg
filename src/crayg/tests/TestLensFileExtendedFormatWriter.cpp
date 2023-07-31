#include "fixtures/CameraLensFixtures.h"
#include "scene/camera/realistic/CameraLens.h"
#include "scene/camera/realistic/lensio/extendedformat/LensFileExtendedFormatWriter.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("LensFileExtendedFormatWriter::writeFileContent") {
    CameraLens canon70_200 = CameraLensFixtures::createCanon70_200mm();
    canon70_200.metadata.patent = "US 123";
    canon70_200.metadata.description = "Super nice lens";

    for (auto &element : canon70_200.elements) {
        element.material.id = LensMaterialId::UNKNOWN;
    }

    SECTION("should ") {
        LensFileExtendedFormatWriter lensFileExtendedFormatWriter;

        const std::string content = lensFileExtendedFormatWriter.writeFileContent(canon70_200);

        REQUIRE(content == R"([Metadata]
Name: Canon F/2.8, 70-200mm
Focal Length: 72.2
Maximum F Number: 3.44
Squeeze: 1
Elements Count: 34
Patent: US 123
Description: Super nice lens
[Elements]
Radius    Thickness IOR  Housing-Radius Abbe-No Material Geometry  
312       2.8       1.75 38             35      UNKNOWN  SPHERICAL 
119       0.42      1    38             0       UNKNOWN  SPHERICAL 
128       8.68      1.5  38             81.6    UNKNOWN  SPHERICAL 
-263      0.1       1    38             0       UNKNOWN  SPHERICAL 
79.5      5.72      1.5  35             86.6    UNKNOWN  SPHERICAL 
203       8.78      1    35             0       UNKNOWN  SPHERICAL 
54.4      2.2       1.85 28             23.8    UNKNOWN  SPHERICAL 
45.9      1.13      1    28             0       UNKNOWN  SPHERICAL 
51.9      8.55      1.49 28             70.2    UNKNOWN  SPHERICAL 
5.1e+03   1.64      1    28             0       UNKNOWN  SPHERICAL 
-489      1.4       1.8  18             46.6    UNKNOWN  SPHERICAL 
35.4      5.88      1    18             0       UNKNOWN  SPHERICAL 
-78.1     1.4       1.49 18             70.2    UNKNOWN  SPHERICAL 
38.1      4.97      1.85 18             23.9    UNKNOWN  SPHERICAL 
417       2.65      1    18             0       UNKNOWN  SPHERICAL 
-66.8     1.4       1.73 18             54.7    UNKNOWN  SPHERICAL 
-3.36e+03 30.3      1    18             0       UNKNOWN  SPHERICAL 
247       3.49      1.7  19             55.5    UNKNOWN  SPHERICAL 
-99.9     0.15      1    19             0       UNKNOWN  SPHERICAL 
-190      4.77      1.5  19             81.6    UNKNOWN  SPHERICAL 
-40.6     1.45      1.83 19             37.2    UNKNOWN  SPHERICAL 
-76.3     14.7      1    19             0       UNKNOWN  SPHERICAL 
58.4      3.53      1.8  21             46.6    UNKNOWN  SPHERICAL 
133       3         1    21             0       UNKNOWN  SPHERICAL 
0         0.24      0    21             0       UNKNOWN  SPHERICAL 
34.1      6.35      1.5  21             81.6    UNKNOWN  SPHERICAL 
2.26e+03  3.72      1.62 21             36.3    UNKNOWN  SPHERICAL 
31.5      28.2      1    21             0       UNKNOWN  SPHERICAL 
133       5.9       1.52 21             52.4    UNKNOWN  SPHERICAL 
-77.5     13.9      1    21             0       UNKNOWN  SPHERICAL 
-39.5     1.8       1.83 21             37.2    UNKNOWN  SPHERICAL 
-95.7     0.15      1    21             0       UNKNOWN  SPHERICAL 
148       3.62      1.74 21             49.3    UNKNOWN  SPHERICAL 
-206      54.5      1    21             0       UNKNOWN  SPHERICAL )");
    }
}

}