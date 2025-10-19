#include "UsdSceneWriter.h"

#include "UsdRenderSettingsWriter.h"
#include "scene/io/write/usd/camera/UsdCameraWriter.h"
#include "scene/io/write/usd/lights/UsdDiskLightWriter.h"
#include "scene/io/write/usd/lights/UsdPointLightWriter.h"
#include "scene/io/write/usd/lights/UsdRectLightWriter.h"
#include "scene/io/write/usd/primitives/UsdGroundPlaneWriter.h"
#include "scene/io/write/usd/primitives/UsdSphereWriter.h"
#include "scene/io/write/usd/primitives/UsdSubdivisionSurfaceMeshWriter.h"
#include "scene/io/write/usd/primitives/UsdTriangleMeshWriter.h"
#include "scene/io/write/usd/shadingnetworks/caches/UsdMaterialWriteCache.h"

void crayg::UsdSceneWriter::writeScene(const std::string &scenePath) {
    auto stage = pxr::UsdStage::CreateNew(scenePath);

    writeScene(stage);

    stage->Save();
}

void crayg::UsdSceneWriter::writeScene(pxr::UsdStagePtr stage) {
    UsdPathFactory usdPathFactory;
    if (scene.camera) {
        UsdCameraWriter(*scene.camera).write(stage, usdPathFactory);
    }

    UsdRenderSettingsWriter(scene.renderSettings).write(stage);
    UsdShadingNodeWriteCache usdShadingNodeWriteCache(stage, usdPathFactory);
    UsdMaterialWriteCache usdMaterialWriteCache(stage, usdPathFactory, usdShadingNodeWriteCache);

    for (auto sceneObject : scene.objects) {
        if (sceneObject->getType() == "Sphere") {
            UsdSphereWriter(*std::static_pointer_cast<Sphere>(sceneObject), usdMaterialWriteCache)
                .write(stage, usdPathFactory);
        } else if (sceneObject->getType() == "TriangleMesh") {
            UsdTriangleMeshWriter(*std::static_pointer_cast<TriangleMesh>(sceneObject), usdMaterialWriteCache)
                .write(stage, usdPathFactory);
        } else if (sceneObject->getType() == "GroundPlane") {
            UsdGroundPlaneWriter(*std::static_pointer_cast<GroundPlane>(sceneObject), usdMaterialWriteCache)
                .write(stage, usdPathFactory);
        } else if (sceneObject->getType() == "SubdivisionSurfaceMesh") {
            UsdSubdivisionSurfaceMeshWriter(*std::static_pointer_cast<SubdivisionSurfaceMesh>(sceneObject),
                                            usdMaterialWriteCache)
                .write(stage, usdPathFactory);
        } else {
            Logger::warning("Skipping unsupported type {}", sceneObject->getType());
        }
    }

    for (auto light : scene.lights) {
        if (light->getType() == "Light") {
            UsdPointLightWriter(*std::static_pointer_cast<Light>(light)).write(stage, usdPathFactory);
        } else if (light->getType() == "RectLight") {
            UsdRectLightWriter(*std::static_pointer_cast<RectLight>(light)).write(stage, usdPathFactory);
        } else if (light->getType() == "DiskLight") {
            UsdDiskLightWriter(*std::static_pointer_cast<DiskLight>(light)).write(stage, usdPathFactory);
        } else {
            Logger::warning("Skipping unsupported type {}", light->getType());
        }
    }
}

crayg::UsdSceneWriter::UsdSceneWriter(crayg::Scene &scene) : SceneWriter(scene) {
}
