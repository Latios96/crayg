//
// Created by Jan on 18.05.2022.
//

#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDSTAGETRANSLATOR_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDSTAGETRANSLATOR_H_

#include "CraygUsdBase.h"
#include "scene/Scene.h"
#include "scene/DiffuseMaterial.h"
#include <pxr/usd/usd/stage.h>

namespace crayg {

class UsdStageTranslator {
 public:
    explicit UsdStageTranslator(pxr::UsdStage &stage);

    void translateStageToScene(Scene &scene);
 private:
    pxr::UsdStage &stage;
    void translateCamera(Scene &scene, const pxr::UsdPrim &prim) const;
    void translateSphereLight(Scene &scene, const pxr::UsdPrim &prim) const;
    void translateUsdGeomMesh(Scene &scene,
                              const std::shared_ptr<DiffuseMaterial> &defaultMaterial,
                              const pxr::UsdPrim &prim) const;
};

}

#endif //CRAYG_SRC_CRAYGUSD_SRC_USDSTAGETRANSLATOR_H_
