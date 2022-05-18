#include <iostream>
#define NOMINMAX
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/camera.h>
#include <pxr/imaging/hd/meshUtil.h>
#include <pxr/imaging/hd/meshTopology.h>
#include <pxr/base/vt/array.h>
#include <scene/TriangleMesh.h>
#include <utils/StopWatch.h>
#include "scene/Scene.h"
#include "image/Image.h"
#include "image/ImageOutputDriver.h"
#include "Renderer.h"
#include "utils/ImagePathResolver.h"
#include "scene/DiffuseMaterial.h"
#include "UsdMeshTranslator.h"
#include "UsdSphereLightTranslator.h"
#include "UsdCameraTranslator.h"
#include <image/ImageWriters.h>

int main(int argc, char *argv[]) {
    crayg::StopWatch stopWatchOpeningState = crayg::StopWatch::createStopWatch("Opening stage");
    //const std::string usdFilePath = "M:\\modelLibrary\\_input_to_convert\\Kitchen_set\\Kitchen_set\\Kitchen_set.usd";
    //const std::string usdFilePath = "M:\\test\\kitchenExportTest.usd";
    //const std::string usdFilePath = "M:\\test\\experimentScene.usd";
    const std::string usdFilePath = "C:\\workspace\\crayg\\debug_scenes\\kitchen_with_camera.usd";
    //const std::string usdFilePath = "M:\\test\\test.usda";
    //const std::string usdFilePath = "M:\\modelLibrary\\_input_to_convert\\USD_ALab_0730\\USD_ALab_0730\\entry.usda";
    //auto stage = pxr::UsdStage::Open("C:\\workspace\\crayg\\example_scenes\\polyPlane.usda");
    auto stage = pxr::UsdStage::Open(usdFilePath);

    crayg::StopWatch stopWatchConvertMeshes = crayg::StopWatch::createStopWatch("Converting meshes");
    crayg::RenderSettings renderSettings(crayg::Resolution(1280, 720), 4);
    crayg::Scene scene;
    scene.renderSettings = renderSettings;

    auto defaultMaterial = std::make_shared<crayg::DiffuseMaterial>("defaultMaterial", crayg::Color::createWhite());

    const int cameraIndexToRender = 0;
    int cameraIndex = 0;

    crayg::Logger::setLevel(crayg::Logger::LevelEnum::debug);

    for (pxr::UsdPrim prim: stage->TraverseAll()) {
        if (prim.IsA<pxr::UsdGeomMesh>()) {
            crayg::Logger::debug("Translating mesh {}", prim.GetPath().GetString());
            auto triangleMesh = crayg::UsdMeshTranslator(pxr::UsdGeomMesh(prim)).translate();
            triangleMesh->init();
            auto randomColor = std::make_shared<crayg::DiffuseMaterial>("defaultMaterial",
                                                                        crayg::Color::createRandom();
            triangleMesh->setMaterial(defaultMaterial);
            scene.addObject(triangleMesh);
        } else if (prim.IsA<pxr::UsdLuxSphereLight>()) {
            crayg::Logger::debug("Translating light {}", prim.GetPath().GetString());
            auto light = crayg::UsdSphereLightTranslator(pxr::UsdLuxSphereLight(prim)).translate();
            scene.addLight(light);
        } else if (prim.IsA<pxr::UsdGeomCamera>()) {
            if (cameraIndex == cameraIndexToRender) {
                crayg::Logger::debug("Using camera {}", prim.GetPath().GetString());
                auto camera = crayg::UsdCameraTranslator(pxr::UsdGeomCamera(prim)).translate();
                crayg::Logger::debug("{}", camera->getPosition());
                scene.camera = camera;
            }
            cameraIndex++;
        }
    }

    stopWatchConvertMeshes.end();

    if (scene.camera == nullptr) {
        crayg::Logger::error("No camera found in USD file {}!", *scene.camera);
        crayg::Logger::error("Abort.");
        exit(1);
    }

    crayg::Image myImage(scene.renderSettings.resolution);

    crayg::ImageOutputDriver imageOutputDriver(myImage);

    crayg::Renderer renderer(scene, imageOutputDriver);
    renderer.renderScene();

    crayg::ImagePathResolver imagePathResolver;
    std::string imageOutputPath = imagePathResolver.resolve("usdexplore.#.png");
    crayg::Logger::info("writing image to {}..", imageOutputPath);
    crayg::ImageWriters::writeImage(myImage, imageOutputPath);
    crayg::Logger::info("writing image done.");

    return 0;
}

