#pragma once

#include "scene/shadingnetworks/ShadingNode.h"
#include "utils/EnumFormatter.h"

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

}

CRAYG_FMT_ENUM_FORMATTER(crayg::PrimVarReaderType);
