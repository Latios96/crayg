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
        UsdFloatConstantReader floatConstantReader(shader);
        return floatConstantReader.read();
    } else if (shadingNodeId == pxr::TfToken("crayg:IntConstant")) {
        UsdIntConstantReader intConstantReader(shader);
        return intConstantReader.read();
    } else if (shadingNodeId == pxr::TfToken("crayg:Vector2fConstant")) {
        UsdVector2fConstantReader vector2fConstantReader(shader);
        return vector2fConstantReader.read();
    } else if (shadingNodeId == pxr::TfToken("crayg:ColorConstant")) {
        UsdColorConstantReader colorConstantReader(shader);
        return colorConstantReader.read();
    } else if (shadingNodeId == pxr::TfToken("crayg:Vector2fToColor")) {
        UsdVector2fToColorReader vector2fToColorReader(shader);
        return vector2fToColorReader.read();
    }

    CRAYG_LOG_AND_THROW(std::runtime_error(fmt::format("ShadingNode of id '{}' is not supported!", shadingNodeId)));
}
} // crayg