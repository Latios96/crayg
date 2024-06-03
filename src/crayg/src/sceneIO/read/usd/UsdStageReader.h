#pragma once

#include "scene/Scene.h"
#include "scene/shadingnetworks/materials/UsdPreviewSurface.h"
#include "sceneIO/read/SceneReader.h"
#include "sceneIO/read/usd/shadingnetworks/caches/UsdMaterialReadCache.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include <optional>
#include <pxr/usd/usd/stage.h>
#include <unordered_set>

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
    void readUsdGeomMesh(Scene &scene, const std::shared_ptr<Material> &defaultMaterial, const pxr::UsdPrim &prim);
    void readSubdivisionSurfaceMesh(Scene &scene, const std::shared_ptr<Material> &defaultMaterial,
                                    const pxr::UsdPrim &prim);
    void readSphere(Scene &scene, const pxr::UsdPrim &prim);
    void readPointInstancer(Scene &scene, const pxr::UsdPrim &prim);
    void readDiskLight(Scene &scene, const pxr::UsdPrim &prim) const;
    void readRenderSettings(Scene &scene);
    bool cameraPathMatches(pxr::SdfPath path, std::optional<std::string> cameraPath);

    UsdMaterialReadCache usdMaterialTranslationCache;

    std::unordered_set<std::string> instancerPrototypeNames;
    void removeAccidentlyReadInstancerProtos(Scene &scene);
    void applyVariantSets(const SceneReader::ReadOptions &readOptions);
};

}
