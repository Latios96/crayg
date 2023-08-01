#include "CameraLensFixtures.h"

namespace crayg {
CameraLens CameraLensFixtures::createCanon70_200mm() {
    // US Patent 5537259
    std::vector<LensElement> elements = {
        {311.919, 2.80, 1.7495, 38.0, 35},   // 0
        {118.63, 0.42, 1, 38.0},             // 1
        {128.135, 8.68, 1.497, 38.0, 81.6},  // 2
        {-263.46, 0.1, 1, 38.0},             // 3
        {79.501, 5.72, 1.497, 35.0, 86.6},   // 4
        {203.191, 8.78, 1, 35.0},            // 5
        {54.391, 2.2, 1.847, 28.0, 23.8},    // 6
        {45.859, 1.13, 1, 28.0},             // 7
        {51.927, 8.55, 1.487, 28.0, 70.2},   // 8
        {5099.30, 1.64, 1, 28.0},            // 9
        {-488.6, 1.4, 1.804, 18.0, 46.6},    // 10
        {35.390, 5.88, 1, 18.0},             // 11
        {-78.125, 1.4, 1.487, 18.0, 70.2},   // 12
        {38.137, 4.97, 1.847, 18.0, 23.9},   // 13
        {417.478, 2.65, 1, 18.0},            // 14
        {-66.802, 1.4, 1.729, 18.0, 54.7},   // 15
        {-3363.0, 30.32, 1, 18.0},           // 16
        {247.12, 3.49, 1.697, 19.0, 55.5},   // 17
        {-99.902, 0.15, 1, 19.0},            // 18
        {-189.99, 4.77, 1.497, 19.0, 81.6},  // 19
        {-40.553, 1.45, 1.834, 19.0, 37.2},  // 20
        {-76.277, 14.7, 1, 19.0},            // 21
        {58.421, 3.53, 1.804, 21.0, 46.6},   // 22
        {133.262, 3, 1, 21.0},               // 23
        {0, 0.24, 0, 21.0},                  // 24
        {34.132, 6.35, 1.497, 21.0, 81.6},   // 25
        {2256.763, 3.72, 1.620, 21.0, 36.3}, // 26
        {31.519, 28.17, 1, 21.0},            // 27
        {132.947, 5.9, 1.517, 21.0, 52.4},   // 28
        {-77.546, 13.94, 1, 21.0},           // 29
        {-39.485, 1.8, 1.834, 21.0, 37.2},   // 30
        {-95.683, 0.15, 1, 21.0},            // 31
        {147.644, 3.62, 1.743, 21.0, 49.3},  // 32
        {-205.76, 54.5, 1, 21.0},            // 33
    };

    const float factor = 0.1f;
    for (auto &element : elements) {
        element.curvatureRadius *= factor;
        element.thickness *= factor;
        element.apertureRadius *= factor;
    }

    return CameraLens(CameraLensMetadata("Canon F/2.8, 70-200mm"), elements);
}

CameraLens CameraLensFixtures::createSchneider30mmAnamorphic() {
    // US Patent 6310731B1
    std::vector<LensElement> elements = {
        {-101.3, 4, 1.591, 60, 61, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), CYLINDER_Y},
        {50, 7.7, 1.762, 60, 27.2, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), CYLINDER_Y},
        {87.3, 71.3, 1, 60, 0, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), CYLINDER_Y},
        {999999, 4.4, 1.711, 56, 30.3, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), SPHERICAL},
        {122.4, 9.5, 1.716, 56, 53.8, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), CYLINDER_Y},
        {-122.4, 2, 1, 56, 0, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), CYLINDER_Y},
        {38.4, 6, 1.681, 36, 54.9, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), SPHERICAL},
        {-783.3, 0.1, 1, 36, 0, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), SPHERICAL},
        {35.9, 3.8, 1.758, 32, 52.3, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), SPHERICAL},
        {55.5, 2.2, 1, 32, 0, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), SPHERICAL},
        {-575.3, 9.2, 1.624, 28, 36.4, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), SPHERICAL},
        {18.8, 3.05, 1, 21, 0, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), SPHERICAL},
        {0, 3.05, 0, 21, 0, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), SPHERICAL},
        {-18.5, 1.5, 1.704, 21, 30.1, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), SPHERICAL},
        {70.7, 1.7, 1, 22, 0, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), SPHERICAL},
        {99.6, 4.4, 1.792, 24, 47.5, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), SPHERICAL},
        {-26, 0.3, 1, 24, 0, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), SPHERICAL},
        {115.2, 3.9, 1.732, 28, 54.7, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), SPHERICAL},
        {-53.2, 43.3809, 1, 28, 0, LensMaterial::createMaterialById(LensMaterialId::UNKNOWN), SPHERICAL},
    };

    const float factor = 0.1f;
    for (auto &element : elements) {
        element.curvatureRadius *= factor;
        element.thickness *= factor;
        element.apertureRadius *= factor;
    }

    return CameraLens(crayg::CameraLensMetadata("Schneider 30mm anamorphic"), elements);
}
} // crayg