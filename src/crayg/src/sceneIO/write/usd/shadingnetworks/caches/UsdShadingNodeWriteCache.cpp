#include "UsdShadingNodeWriteCache.h"
#include "scene/shadingnetworks/shadingnodes/CheckerBoard.h"
#include "scene/shadingnetworks/shadingnodes/ConversionNodes.h"
#include "scene/shadingnetworks/shadingnodes/FileTexture.h"
#include "sceneIO/write/usd/shadingnetworks/shadingnodes/UsdCheckerBoardWriter.h"
#include "sceneIO/write/usd/shadingnetworks/shadingnodes/UsdConstantShadingNodeWriters.h"
#include "sceneIO/write/usd/shadingnetworks/shadingnodes/UsdConversionNodeWriters.h"
#include "sceneIO/write/usd/shadingnetworks/shadingnodes/UsdFileTextureWriter.h"
#include "sceneIO/write/usd/shadingnetworks/shadingnodes/UsdPrimVarReaderWriters.h"
#include "utils/Exceptions.h"

namespace crayg {

UsdShadingNodeWriteCache::UsdShadingNodeWriteCache(const pxr::UsdStagePtr &stage, UsdPathFactory &usdPathFactory)
    : stage(stage), usdPathFactory(usdPathFactory) {
}

void UsdShadingNodeWriteCache::createInputAndWriteCachedGraph(pxr::UsdShadeShader &shader, const std::string &name,
                                                              FloatShadingNodeInput &input) {
    _createInputAndWriteCachedGraph(shader, name, pxr::SdfValueTypeNames->Float, input);
}

void UsdShadingNodeWriteCache::createInputAndWriteCachedGraph(pxr::UsdShadeShader &shader, const std::string &name,
                                                              IntShadingNodeInput &input) {
    _createInputAndWriteCachedGraph(shader, name, pxr::SdfValueTypeNames->Int, input);
}

void UsdShadingNodeWriteCache::createInputAndWriteCachedGraph(pxr::UsdShadeShader &shader, const std::string &name,
                                                              Vector2fShadingNodeInput &input) {
    _createInputAndWriteCachedGraph(shader, name, pxr::SdfValueTypeNames->Float2, input);
}

void UsdShadingNodeWriteCache::createInputAndWriteCachedGraph(pxr::UsdShadeShader &shader, const std::string &name,
                                                              ColorShadingNodeInput &input) {
    _createInputAndWriteCachedGraph(shader, name, pxr::SdfValueTypeNames->Color3f, input);
}

UsdShaderAndOutput &UsdShadingNodeWriteCache::getCachedShadingNode(ShadingNode &shadingNode) {
    const auto shadingNodePath = shadingNode.getName();
    if (materialCache.find(shadingNodePath) == materialCache.end()) {
        materialCache[shadingNodePath] = translateShadingNode(shadingNode);
    }
    return materialCache[shadingNodePath];
}

UsdShaderAndOutput UsdShadingNodeWriteCache::translateShadingNode(ShadingNode &shadingNode) {
    const std::string &type = shadingNode.getType();

    if (type == "FloatConstant") {
        return UsdFloatConstantWriter(dynamic_cast<FloatConstant &>(shadingNode), *this)
            .writeAndGetShaderAndOutput(stage, usdPathFactory);
    } else if (type == "IntConstant") {
        return UsdIntConstantWriter(dynamic_cast<IntConstant &>(shadingNode), *this)
            .writeAndGetShaderAndOutput(stage, usdPathFactory);
    } else if (type == "Vector2fConstant") {
        return UsdVector2fConstantWriter(dynamic_cast<Vector2fConstant &>(shadingNode), *this)
            .writeAndGetShaderAndOutput(stage, usdPathFactory);
    } else if (type == "ColorConstant") {
        return UsdColorConstantWriter(dynamic_cast<ColorConstant &>(shadingNode), *this)
            .writeAndGetShaderAndOutput(stage, usdPathFactory);
    } else if (type == "Vector2fToColor") {
        return UsdVector2fToColorWriter(dynamic_cast<Vector2fToColor &>(shadingNode), *this)
            .writeAndGetShaderAndOutput(stage, usdPathFactory);
    } else if (type == "PrimVarReaderVector2f") {
        return UsdPrimVarReaderVector2fWriter(dynamic_cast<PrimVarReaderVector2f &>(shadingNode), *this)
            .writeAndGetShaderAndOutput(stage, usdPathFactory);
    } else if (type == "CheckerBoard") {
        return UsdCheckerBoardWriter(dynamic_cast<CheckerBoard &>(shadingNode), *this)
            .writeAndGetShaderAndOutput(stage, usdPathFactory);
    } else if (type == "FileTexture") {
        return UsdFileTextureWriter(dynamic_cast<FileTexture &>(shadingNode), *this)
            .writeAndGetShaderAndOutput(stage, usdPathFactory);
    }
    CRAYG_LOG_AND_THROW_RUNTIME_ERROR("ShadingNode of type '{}' is not supported!", type);
}

}