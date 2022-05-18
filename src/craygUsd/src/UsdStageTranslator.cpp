//
// Created by Jan on 18.05.2022.
//

#include "UsdStageTranslator.h"
#include "UsdCameraTranslator.h"
#include "UsdSphereLightTranslator.h"
#include "UsdMeshTranslator.h"
#include "Logger.h"
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/primRange.h>

namespace crayg {

UsdStageTranslator::UsdStageTranslator(pxr::UsdStage &stage) : stage(stage) {}

void UsdStageTranslator::translateStageToScene(Scene &scene, const TranslationsOptions &translationsOptions) {
    scene.renderSettings = translationsOptions.renderSettings.value_or(RenderSettings(crayg::Resolution(1280, 720), 4));

    auto defaultMaterial = std::make_shared<crayg::DiffuseMaterial>("defaultMaterial", crayg::Color::createWhite());

    bool translatedCamera = false;
    for (pxr::UsdPrim prim: stage.TraverseAll()) {
        if (prim.IsA<pxr::UsdGeomMesh>() && primIsVisible(prim)) {
            translateUsdGeomMesh(scene, defaultMaterial, prim);
        } else if (prim.IsA<pxr::UsdLuxSphereLight>() && primIsVisible(prim)) {
            translateSphereLight(scene, prim);
        } else if (prim.IsA<pxr::UsdGeomCamera>() && !translatedCamera) {
            translateCamera(scene, prim);
            translatedCamera = true;
        }
    }

    if (scene.camera == nullptr) {
        throw std::runtime_error("No camera found in USD file!");
    }
}

void UsdStageTranslator::translateUsdGeomMesh(Scene &scene,
                                              const std::shared_ptr<DiffuseMaterial> &defaultMaterial,
                                              const pxr::UsdPrim &prim) const {
    auto triangleMesh = UsdMeshTranslator(pxr::UsdGeomMesh(prim)).translate();
    triangleMesh->init();
    triangleMesh->setMaterial(defaultMaterial);
    scene.addObject(triangleMesh);
}

void UsdStageTranslator::translateSphereLight(Scene &scene, const pxr::UsdPrim &prim) const {
    auto light = UsdSphereLightTranslator(pxr::UsdLuxSphereLight(prim)).translate();
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

}



