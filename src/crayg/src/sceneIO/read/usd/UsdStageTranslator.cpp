//
// Created by Jan on 18.05.2022.
//

#include "UsdStageTranslator.h"
#include "UsdCameraTranslator.h"
#include "UsdSphereLightTranslator.h"
#include "UsdRectLightTranslator.h"
#include "UsdMeshTranslator.h"
#include "UsdSphereTranslator.h"
#include "UsdDiskLightTranslator.h"
#include "Logger.h"
#include "scene/GroundPlane.h"
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/primRange.h>
#include <fmt/format.h>

namespace crayg {

UsdStageTranslator::UsdStageTranslator(pxr::UsdStage &stage) : stage(stage) {}

void UsdStageTranslator::translateStageToScene(Scene &scene, const SceneReader::ReadOptions &readOptions) {
    scene.renderSettings = RenderSettings(crayg::Resolution(1280, 720), 4);

    auto defaultMaterial = std::make_shared<crayg::DiffuseMaterial>("defaultMaterial", crayg::Color::createWhite());

    for (pxr::UsdPrim prim: stage.TraverseAll()) {
        if (prim.IsA<pxr::UsdGeomMesh>() && primIsVisible(prim)) {
            translateUsdGeomMesh(scene, defaultMaterial, prim);
        } else if (prim.IsA<pxr::UsdLuxSphereLight>() && primIsVisible(prim)) {
            translateSphereLight(scene, prim);
        } else if (prim.IsA<pxr::UsdLuxRectLight>() && primIsVisible(prim)) {
            translateRectLight(scene, prim);
        } else if (prim.IsA<pxr::UsdGeomSphere>() && primIsVisible(prim)) {
            translateSphere(scene, prim);
        } else if (prim.IsA<pxr::UsdLuxDiskLight>() && primIsVisible(prim)) {
            translateDiskLight(scene, prim);
        } else if (prim.IsA<pxr::UsdGeomCamera>() && scene.camera == nullptr
            && cameraPathMatches(prim.GetPath(), readOptions.cameraName)) {
            translateCamera(scene, prim);
        }
    }
    const bool noCameraFound = scene.camera == nullptr;
    if (noCameraFound) {
        if (readOptions.cameraName) {
            throw std::runtime_error(fmt::format("No camera with path {} found in USD stage!",
                                                 readOptions.cameraName.value()));
        }
        throw std::runtime_error("No camera found in USD stage!");
    }
}

void UsdStageTranslator::translateUsdGeomMesh(Scene &scene,
                                              const std::shared_ptr<DiffuseMaterial> &defaultMaterial,
                                              const pxr::UsdPrim &prim) {
    auto triangleMesh = UsdMeshTranslator(pxr::UsdGeomMesh(prim), usdMaterialTranslationCache).translate();
    triangleMesh->init();
    scene.addObject(triangleMesh);
}

void UsdStageTranslator::translateSphereLight(Scene &scene, const pxr::UsdPrim &prim) const {
    auto light = UsdSphereLightTranslator(pxr::UsdLuxSphereLight(prim)).translate();
    scene.addLight(light);
}

void UsdStageTranslator::translateRectLight(Scene &scene, const pxr::UsdPrim &prim) const {
    auto light = UsdRectLightTranslator(pxr::UsdLuxRectLight(prim)).translate();
    scene.addLight(light);
}

void UsdStageTranslator::translateCamera(Scene &scene, const pxr::UsdPrim &prim) const {
    Logger::info("Using camera {}", prim.GetPath().GetString());
    auto camera = UsdCameraTranslator(pxr::UsdGeomCamera(prim)).translate();
    scene.camera = camera;
}

bool UsdStageTranslator::primIsVisible(pxr::UsdPrim &prim) {
    return pxr::UsdGeomImageable(prim).ComputeVisibility() != pxr::TfToken("invisible");
}

bool UsdStageTranslator::cameraPathMatches(pxr::SdfPath path, std::optional<std::string> cameraPath) {
    return path.GetString() == cameraPath.value_or(path.GetString());
}

void UsdStageTranslator::translateSphere(Scene &scene, const pxr::UsdPrim &prim) {
    auto sphere = UsdSphereTranslator(pxr::UsdGeomSphere(prim), usdMaterialTranslationCache).translate();
    scene.addObject(sphere);
}
void UsdStageTranslator::translateDiskLight(Scene &scene, const pxr::UsdPrim &prim) const {
    auto diskLight = UsdDiskLightTranslator(pxr::UsdLuxDiskLight(prim)).translate();
    scene.addLight(diskLight);
}

}




