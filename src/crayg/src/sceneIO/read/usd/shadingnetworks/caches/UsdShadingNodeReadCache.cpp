#include "UsdShadingNodeReadCache.h"
#include "sceneIO/read/usd/shadingnetworks/shadingnodes/UsdConstantShadingNodeReaders.h"
#include "sceneIO/read/usd/shadingnetworks/shadingnodes/UsdConversionNodesReaders.h"

namespace crayg {
std::shared_ptr<ShadingNode> UsdShadingNodeReadCache::getCachedOrReadShadingNode(pxr::UsdShadeShader &shader) {
    if (!shader) {
        return nullptr;
    }
    const auto &materialPath = shader.GetPath();
    if (shadingNodeCache.find(materialPath) == shadingNodeCache.end()) {
        shadingNodeCache[materialPath] = translateShadingNode(shader);
    }
    return shadingNodeCache[materialPath];
}

std::shared_ptr<ShadingNode> UsdShadingNodeReadCache::translateShadingNode(pxr::UsdShadeShader &shader) {
    Logger::debug("Translating shading node {}", shader.GetPath());

    const auto &shadingNodeId = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(shader.GetIdAttr());
    if (shadingNodeId == pxr::TfToken("crayg:FloatConstant")) {
        UsdFloatConstantReader floatConstantReader(shader, *this);
        return floatConstantReader.read();
    } else if (shadingNodeId == pxr::TfToken("crayg:IntConstant")) {
        UsdIntConstantReader intConstantReader(shader, *this);
        return intConstantReader.read();
    } else if (shadingNodeId == pxr::TfToken("crayg:Vector2fConstant")) {
        UsdVector2fConstantReader vector2fConstantReader(shader, *this);
        return vector2fConstantReader.read();
    } else if (shadingNodeId == pxr::TfToken("crayg:ColorConstant")) {
        UsdColorConstantReader colorConstantReader(shader, *this);
        return colorConstantReader.read();
    } else if (shadingNodeId == pxr::TfToken("crayg:Vector2fToColor")) {
        UsdVector2fToColorReader vector2fToColorReader(shader, *this);
        return vector2fToColorReader.read();
    }

    Logger::warning("ShadingNode of id '{}' is not supported!", shadingNodeId);

    return nullptr;
}

template <class InputType, typename UsdType, typename T>
void _readCachedGraph(UsdShadingNodeReadCache &usdShadingNodeReadCache, pxr::UsdShadeShader &shader,
                      pxr::UsdShadeInput &source, InputType &target) {
    if (source.GetAttr().HasValue()) {
        target.value = UsdShadingNodeReadUtils::readValue<T, UsdType>(source);
    }

    if (source.HasConnectedSource()) {
        auto connectedShader = UsdUtils::getConnectedUsdShadeShader(shader, source);
        auto cachedConnectedShader = usdShadingNodeReadCache.getCachedOrReadShadingNode(connectedShader);
        target.connectTo(cachedConnectedShader);
    }
}

void UsdShadingNodeReadCache::readCachedGraph(pxr::UsdShadeShader &shader, pxr::UsdShadeInput &source,
                                              FloatShadingNodeInput &target) {
    _readCachedGraph<FloatShadingNodeInput, float, float>(*this, shader, source, target);
}

void UsdShadingNodeReadCache::readCachedGraph(pxr::UsdShadeShader &shader, pxr::UsdShadeInput &source,
                                              IntShadingNodeInput &target) {
    _readCachedGraph<IntShadingNodeInput, int, int>(*this, shader, source, target);
}

void UsdShadingNodeReadCache::readCachedGraph(pxr::UsdShadeShader &shader, pxr::UsdShadeInput &source,
                                              Vector2fShadingNodeInput &target) {
    _readCachedGraph<Vector2fShadingNodeInput, pxr::GfVec2f, Vector2f>(*this, shader, source, target);
}

void UsdShadingNodeReadCache::readCachedGraph(pxr::UsdShadeShader &shader, pxr::UsdShadeInput &source,
                                              ColorShadingNodeInput &target) {
    _readCachedGraph<ColorShadingNodeInput, pxr::GfVec3f, Color>(*this, shader, source, target);
}
} // crayg