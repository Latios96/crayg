//
// Created by Jan on 18.05.2022.
//

#include "UsdStageReader.h"
#include "UsdCameraReader.h"
#include "UsdSphereLightReader.h"
#include "UsdRectLightReader.h"
#include "UsdMeshReader.h"
#include "UsdSphereReader.h"
#include "UsdDiskLightReader.h"
#include "UsdRenderSettingsReader.h"
#include "Logger.h"
#include "scene/GroundPlane.h"
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/primRange.h>
#include <fmt/format.h>

namespace crayg {

UsdStageReader::UsdStageReader(pxr::UsdStage &stage) : stage(stage) {}

void UsdStageReader::readStageToScene(Scene &scene, const SceneReader::ReadOptions &readOptions) {
    readRenderSettings(scene);

    auto defaultMaterial = std::make_shared<crayg::DiffuseMaterial>("defaultMaterial", crayg::Color::createWhite());

    for (pxr::UsdPrim prim: stage.TraverseAll()) {
        if (prim.IsA<pxr::UsdGeomMesh>() && primIsVisible(prim)) {
            readUsdGeomMesh(scene, defaultMaterial, prim);
        } else if (prim.IsA<pxr::UsdLuxSphereLight>() && primIsVisible(prim)) {
            readSphereLight(scene, prim);
        } else if (prim.IsA<pxr::UsdLuxRectLight>() && primIsVisible(prim)) {
            readRectLight(scene, prim);
        } else if (prim.IsA<pxr::UsdGeomSphere>() && primIsVisible(prim)) {
            readSphere(scene, prim);
        } else if (prim.IsA<pxr::UsdLuxDiskLight>() && primIsVisible(prim)) {
            readDiskLight(scene, prim);
        } else if (prim.IsA<pxr::UsdGeomCamera>() && scene.camera == nullptr
            && cameraPathMatches(prim.GetPath(), readOptions.cameraName)) {
            readCamera(scene, prim);
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

void UsdStageReader::readUsdGeomMesh(Scene &scene,
                                     const std::shared_ptr<DiffuseMaterial> &defaultMaterial,
                                     const pxr::UsdPrim &prim) {
    auto triangleMesh = UsdMeshReader(pxr::UsdGeomMesh(prim), usdMaterialTranslationCache).read();
    triangleMesh->init();
    scene.addObject(triangleMesh);
}

void UsdStageReader::readSphereLight(Scene &scene, const pxr::UsdPrim &prim) const {
    auto light = UsdSphereLightReader(pxr::UsdLuxSphereLight(prim)).read();
    scene.addLight(light);
}

void UsdStageReader::readRectLight(Scene &scene, const pxr::UsdPrim &prim) const {
    auto light = UsdRectLightReader(pxr::UsdLuxRectLight(prim)).read();
    scene.addLight(light);
}

void UsdStageReader::readCamera(Scene &scene, const pxr::UsdPrim &prim) const {
    Logger::info("Using camera {}", prim.GetPath().GetString());
    auto camera = UsdCameraReader(pxr::UsdGeomCamera(prim)).read();
    scene.camera = camera;
}

bool UsdStageReader::primIsVisible(pxr::UsdPrim &prim) {
    return pxr::UsdGeomImageable(prim).ComputeVisibility() != pxr::TfToken("invisible");
}

bool UsdStageReader::cameraPathMatches(pxr::SdfPath path, std::optional<std::string> cameraPath) {
    return path.GetString() == cameraPath.value_or(path.GetString());
}

void UsdStageReader::readSphere(Scene &scene, const pxr::UsdPrim &prim) {
    auto sphere = UsdSphereReader(pxr::UsdGeomSphere(prim), usdMaterialTranslationCache).read();
    scene.addObject(sphere);
}

void UsdStageReader::readDiskLight(Scene &scene, const pxr::UsdPrim &prim) const {
    auto diskLight = UsdDiskLightReader(pxr::UsdLuxDiskLight(prim)).read();
    scene.addLight(diskLight);
}

void UsdStageReader::readRenderSettings(Scene &scene) {
    const pxr::UsdPrim renderPrim = stage.GetPrimAtPath(pxr::SdfPath("/Render"));
    if (!renderPrim) {
        scene.renderSettings = RenderSettings(crayg::Resolution(1280, 720), 4);
        return;
    }
    for (pxr::UsdPrim prim: renderPrim.GetDescendants()) {
        if (prim.IsA<pxr::UsdRenderSettings>()) {
            scene.renderSettings = *UsdRenderSettingsReader(pxr::UsdRenderSettings(prim)).read();
            return;
        }
    }
    scene.renderSettings = RenderSettings(crayg::Resolution(1280, 720), 4);
}

}




