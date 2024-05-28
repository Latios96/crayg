#ifndef CRAYG_SRC_CRAYG_TESTS_FIXTURES_UNITPLANEUVS_H_
#define CRAYG_SRC_CRAYG_TESTS_FIXTURES_UNITPLANEUVS_H_

#include "integrators/SurfaceInteraction.h"
#include "scene/shadingnetworks/ShadingNode.h"

namespace crayg {

class UnitPlaneUvs : public ShadingNode {
  public:
    Vector2f evaluateVector2f(const SurfaceInteraction &surfaceInteraction) override {
        return surfaceInteraction.point.xy();
    }

    std::string getType() const override {
        return "UnitPlaneUvs";
    }

    ShadingNodeOutputType getOutputType() override {
        return ShadingNodeOutputType::VECTOR2F;
    }
};

}

#endif // CRAYG_SRC_CRAYG_TESTS_FIXTURES_UNITPLANEUVS_H_
