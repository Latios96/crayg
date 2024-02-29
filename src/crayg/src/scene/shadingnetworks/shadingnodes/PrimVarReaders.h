#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNETWORKS_SHADINGNODES_PRIMVARREADERS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNETWORKS_SHADINGNODES_PRIMVARREADERS_H_

#include "scene/shadingnetworks/ShadingNode.h"

namespace crayg {

enum class PrimVarReaderType { UNKNOWN, UV, NORMAL };

class PrimVarReaderVector2f : public ShadingNode {
  public:
    PrimVarReaderVector2f() = default;
    std::string getType() const override;
    ShadingNodeOutputType getOutputType() override;

    Vector2f evaluateVector2f(const SurfaceInteraction &surfaceInteraction) override;
    PrimVarReaderType primVarReaderType = PrimVarReaderType::UNKNOWN;

  private:
    Vector2f readUvs(const SurfaceInteraction &surfaceInteraction);
};

} // crayg

CRAYG_FMT_ENUM_FORMATTER(crayg::PrimVarReaderType);

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNETWORKS_SHADINGNODES_PRIMVARREADERS_H_
