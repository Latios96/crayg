#include "UsdStageReader.h"
#include "Logger.h"
#include "UsdCameraReader.h"
#include "UsdDiskLightReader.h"
#include "UsdMeshReader.h"
#include "UsdRectLightReader.h"
#include "UsdRenderSettingsReader.h"
#include "UsdSphereLightReader.h"
#include "UsdSphereReader.h"
#include "UsdSubdivisionSurfaceMeshReader.h"
#include "scene/primitives/GroundPlane.h"
#include <fmt/format.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/primFlags.h>
#include <pxr/usd/usd/primRange.h>

namespace crayg {

UsdStageReader::UsdStageReader(pxr::UsdStage &stage) : stage(stage) {
}

void UsdStageReader::readStageToScene(Scene &scene, const SceneReader::ReadOptions &readOptions) {
    readRenderSettings(scene);

    auto defaultMaterial = std::make_shared<crayg::UsdPreviewSurface>("defaultMaterial", crayg::Color::createWhite());

    for (pxr::UsdPrim prim : stage.Traverse(pxr::UsdTraverseInstanceProxies())) {
        if (isSubdivisionSurfaceMesh(prim) && primIsVisible(prim)) {
            readSubdivisionSurfaceMesh(scene, defaultMaterial, prim);
        } else if (prim.IsA<pxr::UsdGeomMesh>() && primIsVisible(prim)) {
            readUsdGeomMesh(scene, defaultMaterial, prim);
        } else if (prim.IsA<pxr::UsdLuxSphereLight>() && primIsVisible(prim)) {
            readSphereLight(scene, prim);
        } else if (prim.IsA<pxr::UsdLuxRectLight>() && primIsVisible(prim)) {
            readRectLight(scene, prim);
        } else if (prim.IsA<pxr::UsdGeomSphere>() && primIsVisible(prim)) {
            readSphere(scene, prim);
        } else if (prim.IsA<pxr::UsdLuxDiskLight>() && primIsVisible(prim)) {
            readDiskLight(scene, prim);
        } else if (prim.IsA<pxr::UsdGeomCamera>() && scene.camera == nullptr &&
                   cameraPathMatches(prim.GetPath(), readOptions.cameraName)) {
            readCamera(scene, prim);
        }
    }
    const bool noCameraFound = scene.camera == nullptr;
    if (noCameraFound) {
        if (readOptions.cameraName) {
            throw std::runtime_error(
                fmt::format("No camera with path {} found in USD stage!", readOptions.cameraName.value()));
        }
        throw std::runtime_error("No camera found in USD stage!");
    }
}

void UsdStageReader::readUsdGeomMesh(Scene &scene, const std::shared_ptr<Material> &defaultMaterial,
                                     const pxr::UsdPrim &prim) {
    auto triangleMesh = UsdMeshReader(pxr::UsdGeomMesh(prim), usdMaterialTranslationCache).read();
    triangleMesh->init();
    scene.addObject(triangleMesh);
}

void UsdStageReader::readSubdivisionSurfaceMesh(Scene &scene, const std::shared_ptr<Material> &defaultMaterial,
                                                const pxr::UsdPrim &prim) {
    auto subdivisionSurfaceMesh =
        UsdSubdivisionSurfaceMeshReader(pxr::UsdGeomMesh(prim), usdMaterialTranslationCache).read();
    scene.addObject(subdivisionSurfaceMesh);
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
    Logger::info("Using camera {}", prim.GetPath());
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
        scene.renderSettings = RenderSettings::createDefault();
        return;
    }
    for (pxr::UsdPrim prim : renderPrim.GetDescendants()) {
        if (prim.IsA<pxr::UsdRenderSettings>()) {
            scene.renderSettings = *UsdRenderSettingsReader(pxr::UsdRenderSettings(prim)).read();
            return;
        }
    }
    scene.renderSettings = RenderSettings::createDefault();
}

bool UsdStageReader::isSubdivisionSurfaceMesh(pxr::UsdPrim &prim) {
    if (!prim.IsA<pxr::UsdGeomMesh>()) {
        return false;
    }
    pxr::UsdGeomMesh usdGeomMesh(prim);
    auto subdivisionScheme = UsdUtils::getAttributeValueAs<pxr::TfToken>(usdGeomMesh.GetSubdivisionSchemeAttr(),
                                                                         pxr::UsdTimeCode::EarliestTime());
    return subdivisionScheme == pxr::UsdGeomTokens->catmullClark;
}

}
