#include "UsdShadingNodeWriteCache.h"
#include "UsdConstantShadingNodeWriters.h"

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
    // todo make recursive writes possible
    if (type == "FloatConstant") {
        return UsdFloatConstantWriter(dynamic_cast<FloatConstant &>(shadingNode))
            .writeAndGetShaderAndOutput(stage, usdPathFactory);
    } else if (type == "IntConstant") {
        return UsdIntConstantWriter(dynamic_cast<IntConstant &>(shadingNode))
            .writeAndGetShaderAndOutput(stage, usdPathFactory);
    } else if (type == "Vector2fConstant") {
        return UsdVector2fConstantWriter(dynamic_cast<Vector2fConstant &>(shadingNode))
            .writeAndGetShaderAndOutput(stage, usdPathFactory);
    } else if (type == "ColorConstant") {
        return UsdColorConstantWriter(dynamic_cast<ColorConstant &>(shadingNode))
            .writeAndGetShaderAndOutput(stage, usdPathFactory);
    }
    throw std::runtime_error(fmt::format("ShadingNode of type '' is not supported!", type));
}

} // crayg