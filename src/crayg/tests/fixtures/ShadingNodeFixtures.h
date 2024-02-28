#ifndef CRAYG_SRC_CRAYG_TESTS_FIXTURES_SHADINGNODEFIXTURES_H_
#define CRAYG_SRC_CRAYG_TESTS_FIXTURES_SHADINGNODEFIXTURES_H_

#include "scene/shadingnetworks/materials/Material.h"

namespace crayg {

class ShaderForTesting : public Material {
  public:
    ShaderForTesting();

    ColorShadingNodeInput colorInput;
    FloatShadingNodeInput reflectivity;
};
} // crayg

#endif // CRAYG_SRC_CRAYG_TESTS_FIXTURES_SHADINGNODEFIXTURES_H_
