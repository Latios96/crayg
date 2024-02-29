#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_SHADINGNETWORKS_CACHES_USDSHADINGNODEREADCACHE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_SHADINGNETWORKS_CACHES_USDSHADINGNODEREADCACHE_H_

#include "sceneIO/read/usd/base/BaseUsdShadingNodeReader.h"
#include "sceneIO/usd/UsdConversions.h"
#include "sceneIO/usd/UsdUtils.h"
#include <memory>
#include <pxr/usd/usdShade/shader.h>
#include <scene/shadingnetworks/ShadingNode.h>

namespace crayg {

class UsdShadingNodeReadCache {
  public:
    std::shared_ptr<ShadingNode> getCachedOrReadShadingNode(pxr::UsdShadeShader &shader);

    void readCachedGraph(pxr::UsdShadeShader &shader, pxr::UsdShadeInput &source, FloatShadingNodeInput &target) {
        _readCachedGraph<FloatShadingNodeInput, float, float>(shader, source, target);
    }

    void readCachedGraph(pxr::UsdShadeShader &shader, pxr::UsdShadeInput &source, IntShadingNodeInput &target) {
        _readCachedGraph<IntShadingNodeInput, int, int>(shader, source, target);
    }

    void readCachedGraph(pxr::UsdShadeShader &shader, pxr::UsdShadeInput &source, Vector2fShadingNodeInput &target) {
        _readCachedGraph<Vector2fShadingNodeInput, pxr::GfVec2f, Vector2f>(shader, source, target);
    }

    void readCachedGraph(pxr::UsdShadeShader &shader, pxr::UsdShadeInput &source, ColorShadingNodeInput &target) {
        _readCachedGraph<ColorShadingNodeInput, pxr::GfVec3f, Color>(shader, source, target);
    }

  private:
    template <class InputType, typename UsdType, typename T>
    void _readCachedGraph(pxr::UsdShadeShader &shader, pxr::UsdShadeInput &source, InputType &target) {
        target.value = UsdShadingNodeReadUtils::readValue<T, UsdType>(source);

        if (source.HasConnectedSource()) {
            auto connectedShader = UsdUtils::getConnectedUsdShadeShader(shader, source);
            auto cachedConnectedShader = getCachedOrReadShadingNode(connectedShader);
            target.connectTo(cachedConnectedShader);
        }
    }

    std::shared_ptr<ShadingNode> translateShadingNode(pxr::UsdShadeShader &shader);
    std::map<pxr::SdfPath, std::shared_ptr<ShadingNode>> shadingNodeCache;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_SHADINGNETWORKS_CACHES_USDSHADINGNODEREADCACHE_H_
