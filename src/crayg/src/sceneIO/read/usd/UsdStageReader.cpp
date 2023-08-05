#include "UsdStageReader.h"
#include "Logger.h"
#include "UsdCameraReader.h"
#include "UsdDiskLightReader.h"
#include "UsdMeshReader.h"
#include "UsdPointInstancerReader.h"
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
#include <pxr/usd/usdGeom/pointInstancer.h>

namespace crayg {

UsdStageReader::UsdStageReader(pxr::UsdStage &stage) : stage(stage) {
}

void UsdStageReader::readStageToScene(Scene &scene, const SceneReader::ReadOptions &readOptions) {
    applyVariantSets(readOptions);

    readRenderSettings(scene);

    auto defaultMaterial = std::make_shared<crayg::UsdPreviewSurface>("defaultMaterial", crayg::Color::createWhite());

    for (pxr::UsdPrim prim : stage.Traverse(pxr::UsdTraverseInstanceProxies())) {
        if (UsdReadUtils::isSubdivisionSurfaceMesh(prim) && UsdReadUtils::primIsVisible(prim)) {
            readSubdivisionSurfaceMesh(scene, defaultMaterial, prim);
        } else if (prim.IsA<pxr::UsdGeomMesh>() && UsdReadUtils::primIsVisible(prim)) {
            readUsdGeomMesh(scene, defaultMaterial, prim);
        } else if (prim.IsA<pxr::UsdLuxSphereLight>() && UsdReadUtils::primIsVisible(prim)) {
            readSphereLight(scene, prim);
        } else if (prim.IsA<pxr::UsdLuxRectLight>() && UsdReadUtils::primIsVisible(prim)) {
            readRectLight(scene, prim);
        } else if (prim.IsA<pxr::UsdGeomSphere>() && UsdReadUtils::primIsVisible(prim)) {
            readSphere(scene, prim);
        } else if (prim.IsA<pxr::UsdGeomPointInstancer>() && UsdReadUtils::primIsVisible(prim)) {
            readPointInstancer(scene, prim);
        } else if (prim.IsA<pxr::UsdLuxDiskLight>() && UsdReadUtils::primIsVisible(prim)) {
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

    removeAccidentlyReadInstancerProtos(scene);
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

void UsdStageReader::readPointInstancer(Scene &scene, const pxr::UsdPrim &prim) {
    auto pointInstancer = UsdPointInstancerReader(pxr::UsdGeomPointInstancer(prim), usdMaterialTranslationCache).read();
    scene.addObject(pointInstancer);
    pointInstancer->init();
    for (auto &proto : pointInstancer->protos) {
        for (auto &member : proto->members) {
            instancerPrototypeNames.insert(member->getName());
        }
    }
}

void UsdStageReader::removeAccidentlyReadInstancerProtos(Scene &scene) {
    for (int i = 0; i < scene.objects.size(); i++) {
        if (instancerPrototypeNames.find(scene.objects[i]->getName()) != instancerPrototypeNames.end()) {
            scene.objects.erase(scene.objects.begin() + i);
            i--;
        }
    }
}

void UsdStageReader::applyVariantSets(const SceneReader::ReadOptions &readOptions) {
    for (auto &variantSelection : readOptions.variantSelections) {
        pxr::UsdPrim prim = stage.GetPrimAtPath(pxr::SdfPath(variantSelection.primPath));
        if (!prim.IsValid()) {
            throw std::runtime_error(fmt::format("Error when applying variant selections: invalid prim path {}.",
                                                 variantSelection.primPath));
        }

        const auto variantSetNames = prim.GetVariantSets().GetNames();
        const bool variantSetExists = std::any_of(variantSetNames.begin(), variantSetNames.end(),
                                                  [&variantSelection](const auto &variantSetName) {
                                                      return variantSetName == variantSelection.variantSetName;
                                                  });
        if (!variantSetExists) {
            throw std::runtime_error(fmt::format(
                "Error when applying variant selections: variant set with name '{}' does not exist on prim {}.",
                variantSelection.variantSetName, variantSelection.primPath));
        }
        auto variantSet = prim.GetVariantSet(variantSelection.variantSetName);

        const auto variantNames = variantSet.GetVariantNames();
        const bool variantExists =
            std::any_of(variantNames.begin(), variantNames.end(), [&variantSelection](const auto &variantName) {
                return variantName == variantSelection.selectedVariant;
            });
        if (!variantExists) {
            throw std::runtime_error(fmt::format("Error when applying variant selections: variant with name '{}' does "
                                                 "not exist on variant set '{}'on prim {}.",
                                                 variantSelection.selectedVariant, variantSelection.variantSetName,
                                                 variantSelection.primPath));
        }
        if (!variantSet.SetVariantSelection(variantSelection.selectedVariant)) {
            throw std::runtime_error(fmt::format("Error when applying variant selections: could not set variant with "
                                                 "name '{}' does on variant set '{}'on prim {}.",
                                                 variantSelection.selectedVariant, variantSelection.variantSetName,
                                                 variantSelection.primPath));
        }
        Logger::info("Applied variant selection: set variant set '{}' on {} to '{}'", variantSelection.variantSetName,
                     variantSelection.primPath, variantSelection.selectedVariant);
    }
}
}
