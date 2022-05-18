#define NOMINMAX
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <utils/StopWatch.h>
#include "scene/Scene.h"
#include "image/Image.h"
#include "image/ImageOutputDriver.h"
#include "Renderer.h"
#include "utils/ImagePathResolver.h"
#include "scene/DiffuseMaterial.h"
#include "sceneIO/read/usd/UsdMeshTranslator.h"
#include "sceneIO/read/usd/UsdSphereLightTranslator.h"
#include "sceneIO/read/usd/UsdCameraTranslator.h"
#include "sceneIO/read/usd/UsdStageTranslator.h"
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

    crayg::Scene scene;
    crayg::UsdStageTranslator translator(*stage);
    translator.translateStageToScene(scene);

    stopWatchConvertMeshes.end();

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

