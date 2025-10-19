#pragma once

#include "crayg/scene/io/usd/UsdConversions.h"
#include "crayg/scene/io/usd/UsdUtils.h"
#include "crayg/scene/shadingnetworks/ShadingNode.h"
#include <memory>
#include <pxr/usd/usdShade/shader.h>

namespace crayg {

class UsdShadingNodeReadCache {
  public:
    std::shared_ptr<ShadingNode> getCachedOrReadShadingNode(pxr::UsdShadeShader &shader);

    void readCachedGraph(pxr::UsdShadeShader &shader, pxr::UsdShadeInput &source, FloatShadingNodeInput &target);

    void readCachedGraph(pxr::UsdShadeShader &shader, pxr::UsdShadeInput &source, IntShadingNodeInput &target);

    void readCachedGraph(pxr::UsdShadeShader &shader, pxr::UsdShadeInput &source, Vector2fShadingNodeInput &target);

    void readCachedGraph(pxr::UsdShadeShader &shader, pxr::UsdShadeInput &source, ColorShadingNodeInput &target);

  private:
    std::shared_ptr<ShadingNode> translateShadingNode(pxr::UsdShadeShader &shader);
    std::map<pxr::SdfPath, std::shared_ptr<ShadingNode>> shadingNodeCache;
};

}
