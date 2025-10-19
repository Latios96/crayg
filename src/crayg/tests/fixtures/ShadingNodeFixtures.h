#pragma once

#include "crayg/scene/shadingnetworks/materials/Material.h"

namespace crayg {

class ShaderForTesting : public Material {
  public:
    ShaderForTesting();

    ColorShadingNodeInput colorInput;
    FloatShadingNodeInput reflectivity;
};
}
