#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDSTAGETRANSLATOR_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDSTAGETRANSLATOR_H_

#include "sceneIO/usd/CraygUsdBase.h"
#include "scene/Scene.h"
#include "scene/materials/UsdPreviewSurface.h"
#include "sceneIO/read/SceneReader.h"
#include "UsdMaterialReadCache.h"
#include <pxr/usd/usd/stage.h>
#include <optional>

namespace crayg {

class UsdStageReader {
 public:

    explicit UsdStageReader(pxr::UsdStage &stage);

    void readStageToScene(Scene &scene,
                          const SceneReader::ReadOptions &readOptions = SceneReader::ReadOptions::empty());

 private:
    pxr::UsdStage &stage;
    void readCamera(Scene &scene, const pxr::UsdPrim &prim) const;
    void readSphereLight(Scene &scene, const pxr::UsdPrim &prim) const;
    void readRectLight(Scene &scene, const pxr::UsdPrim &prim) const;
    void readUsdGeomMesh(Scene &scene,
                         const std::shared_ptr<Material> &defaultMaterial,
                         const pxr::UsdPrim &prim);
    void readSphere(Scene &scene, const pxr::UsdPrim &prim);
    void readDiskLight(Scene &scene, const pxr::UsdPrim &prim) const;
    void readRenderSettings(Scene &scene);
    bool primIsVisible(pxr::UsdPrim &prim);
    bool cameraPathMatches(pxr::SdfPath path, std::optional<std::string> cameraPath);

    UsdMaterialReadCache usdMaterialTranslationCache;
};

}

#endif //CRAYG_SRC_CRAYGUSD_SRC_USDSTAGETRANSLATOR_H_
