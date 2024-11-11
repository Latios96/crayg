#include "UsdShadingNodeReadCache.h"
#include "scene/shadingnetworks/shadingnodes/ColorToFloat.h"
#include "sceneIO/read/usd/shadingnetworks/shadingnodes/UsdCheckerBoardReader.h"
#include "sceneIO/read/usd/shadingnetworks/shadingnodes/UsdConstantShadingNodeReaders.h"
#include "sceneIO/read/usd/shadingnetworks/shadingnodes/UsdConversionNodesReaders.h"
#include "sceneIO/read/usd/shadingnetworks/shadingnodes/UsdFileTextureReader.h"
#include "sceneIO/read/usd/shadingnetworks/shadingnodes/UsdPrimVarReaderReaders.h"

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
    } else if (shadingNodeId == pxr::TfToken("UsdPrimvarReader_float2") ||
               shadingNodeId == pxr::TfToken("crayg:PrimVarReaderVector2f")) {
        UsdPrimVarReaderVector2fReader primVarReaderVector2fReader(shader, *this);
        return primVarReaderVector2fReader.read();
    } else if (shadingNodeId == pxr::TfToken("crayg:CheckerBoard")) {
        UsdCheckerBoardReader checkerBoardReader(shader, *this);
        return checkerBoardReader.read();
    } else if (shadingNodeId == pxr::TfToken("UsdUVTexture") || shadingNodeId == pxr::TfToken("crayg:FileTexture")) {
        UsdFileTextureReader fileTextureReader(shader, *this);
        return fileTextureReader.read();
    }

    Logger::warning("ShadingNode of id '{}' is not supported!", shadingNodeId);

    return nullptr;
}

std::shared_ptr<ShadingNode> insertAutomaticConversion(std::shared_ptr<ShadingNode> &cachedConnectedShader,
                                                       const pxr::TfToken &connectedOutputName,
                                                       ShadingNodeOutputType outputType,
                                                       ShadingNodeOutputType inputType) {
    const bool isColorToFloat = outputType == ShadingNodeOutputType::COLOR && inputType == ShadingNodeOutputType::FLOAT;

    if (isColorToFloat) {
        auto colorToFloat = std::make_shared<ColorToFloat>();
        colorToFloat->colorInput.connectTo(cachedConnectedShader);
        if (connectedOutputName == "r") {
            colorToFloat->colorToFloatMode = ColorToFloatMode::R;
        } else if (connectedOutputName == "g") {
            colorToFloat->colorToFloatMode = ColorToFloatMode::G;
        } else if (connectedOutputName == "b") {
            colorToFloat->colorToFloatMode = ColorToFloatMode::B;
        }
        return colorToFloat;
    }

    CRAYG_LOG_AND_THROW_MESSAGE(
        fmt::format("Error when connecting {}.{}. Output type {} can not be connected to input type {} "
                    "and no automatic conversion is defined",
                    cachedConnectedShader->getName(), connectedOutputName, outputType, inputType));
}

template <class InputType, typename UsdType, typename T>
void _readCachedGraph(UsdShadingNodeReadCache &usdShadingNodeReadCache, pxr::UsdShadeShader &shader,
                      pxr::UsdShadeInput &source, InputType &target) {
    if (source.GetAttr().HasValue()) {
        target.value = UsdShadingNodeReadUtils::readValue<T, UsdType>(source);
    }

    if (source.HasConnectedSource()) {
        pxr::TfToken connectedOutputName;
        auto connectedShader = UsdUtils::getConnectedUsdShadeShader(shader, source, connectedOutputName);
        auto cachedConnectedShader = usdShadingNodeReadCache.getCachedOrReadShadingNode(connectedShader);

        const ShadingNodeOutputType outputType = cachedConnectedShader->getOutputType();
        const ShadingNodeOutputType inputType = target.getOutputType();
        if (outputType != inputType) {
            cachedConnectedShader =
                insertAutomaticConversion(cachedConnectedShader, connectedOutputName, outputType, inputType);
        }

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