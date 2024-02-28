#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_MATERIALS_USDSHADINGNODEWRITECACHE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_MATERIALS_USDSHADINGNODEWRITECACHE_H_
#include "scene/shadingnetworks/ShadingNode.h"
#include "sceneIO/usd/UsdConversions.h"
#include "sceneIO/write/usd/UsdPathFactory.h"
#include "sceneIO/write/usd/base/BaseUsdShadingNodeWriter.h"
#include <map>
#include <pxr/usd/usdShade/shader.h>

namespace crayg {

// todo restructure: rename "materials" folder to "shadingnetworks", create subfolders for shadingnodes and materials
// and a "caches" folder. create this structure in both USD io and in prod code
class UsdShadingNodeWriteCache {

  public:
    UsdShadingNodeWriteCache(const pxr::UsdStagePtr &stage, UsdPathFactory &usdPathFactory);
    // todo test these individually
    void createInputAndWriteCachedGraph(pxr::UsdShadeShader &shader, const std::string &name,
                                        FloatShadingNodeInput &input);
    void createInputAndWriteCachedGraph(pxr::UsdShadeShader &shader, const std::string &name,
                                        IntShadingNodeInput &input);
    void createInputAndWriteCachedGraph(pxr::UsdShadeShader &shader, const std::string &name,
                                        Vector2fShadingNodeInput &input);
    void createInputAndWriteCachedGraph(pxr::UsdShadeShader &shader, const std::string &name,
                                        ColorShadingNodeInput &input);

  private:
    template <class InputType>
    void _createInputAndWriteCachedGraph(pxr::UsdShadeShader &shader, const std::string &name,
                                         pxr::SdfValueTypeName type, InputType &input) {
        auto usdInput = shader.CreateInput(pxr::TfToken(name), type);
        usdInput.Set(UsdConversions::convert(input.value));
        if (!input.hasInputConnection()) {
            return;
        }

        auto cacheEntry = getCachedShadingNode(*input.inputNode);
        if (cacheEntry.output) {
            usdInput.ConnectToSource(cacheEntry.output);
        }
    }

    UsdShaderAndOutput &getCachedShadingNode(ShadingNode &shadingNode);

    UsdShaderAndOutput translateShadingNode(ShadingNode &shadingNode);

    std::map<std::string, UsdShaderAndOutput> materialCache;
    pxr::UsdStagePtr stage;
    UsdPathFactory &usdPathFactory;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_MATERIALS_USDSHADINGNODEWRITECACHE_H_
