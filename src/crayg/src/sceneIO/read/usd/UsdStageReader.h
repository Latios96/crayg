#pragma once

#include "scene/Scene.h"
#include "scene/shadingnetworks/materials/UsdPreviewSurface.h"
#include "sceneIO/read/SceneReader.h"
#include "sceneIO/read/usd/shadingnetworks/caches/UsdMaterialReadCache.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include <optional>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdRender/settings.h>
#include <unordered_set>

namespace crayg {

class UsdStageReader {
  public:
    explicit UsdStageReader(pxr::UsdStage &stage);

    void readStageToScene(Scene &scene,
                          const SceneReader::ReadOptions &readOptions = SceneReader::ReadOptions::empty());

  private:
    pxr::UsdStage &stage;
    std::optional<pxr::SdfPath> cameraFromUsdRenderSettings;
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
    bool shouldReadCamera(const Scene &scene, const pxr::UsdPrim &prim,
                          const SceneReader::ReadOptions &readOptions) const;
    bool cameraPathMatches(const pxr::SdfPath &path, const std::optional<std::string> &cameraPath) const;

    UsdMaterialReadCache usdMaterialTranslationCache;

    std::unordered_set<std::string> instancerPrototypeNames;
    void removeAccidentlyReadInstancerProtos(Scene &scene);
    void applyVariantSets(const SceneReader::ReadOptions &readOptions);
};

}
