//
// Created by Jan on 18.05.2022.
//

#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDSTAGETRANSLATOR_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDSTAGETRANSLATOR_H_

#include "CraygUsdBase.h"
#include "scene/Scene.h"
#include "scene/DiffuseMaterial.h"
#include <pxr/usd/usd/stage.h>
#include <optional>

namespace crayg {

class UsdStageTranslator {
 public:

    struct TranslationsOptions {
        std::optional<std::string> cameraPath;
        std::optional<RenderSettings> renderSettings;
        static TranslationsOptions empty() {
            return {};
        }
    };

    explicit UsdStageTranslator(pxr::UsdStage &stage);

    void translateStageToScene(Scene &scene,
                               const TranslationsOptions &TranslationsOptions = TranslationsOptions::empty());

 private:
    pxr::UsdStage &stage;
    void translateCamera(Scene &scene, const pxr::UsdPrim &prim) const;
    void translateSphereLight(Scene &scene, const pxr::UsdPrim &prim) const;
    void translateUsdGeomMesh(Scene &scene,
                              const std::shared_ptr<DiffuseMaterial> &defaultMaterial,
                              const pxr::UsdPrim &prim) const;
    bool primIsVisible(pxr::UsdPrim &prim);
    bool cameraPathMatches(pxr::SdfPath path, std::optional<std::string> cameraPath);
};

}

#endif //CRAYG_SRC_CRAYGUSD_SRC_USDSTAGETRANSLATOR_H_
