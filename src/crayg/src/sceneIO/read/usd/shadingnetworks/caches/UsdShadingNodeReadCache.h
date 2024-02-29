#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_SHADINGNETWORKS_CACHES_USDSHADINGNODEREADCACHE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_SHADINGNETWORKS_CACHES_USDSHADINGNODEREADCACHE_H_

#include "sceneIO/read/usd/shadingnetworks/UsdShadingNodeReadUtils.h"
#include "sceneIO/usd/UsdConversions.h"
#include "sceneIO/usd/UsdUtils.h"
#include <memory>
#include <pxr/usd/usdShade/shader.h>
#include <scene/shadingnetworks/ShadingNode.h>

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

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_SHADINGNETWORKS_CACHES_USDSHADINGNODEREADCACHE_H_
