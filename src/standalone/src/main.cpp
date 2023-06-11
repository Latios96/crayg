#include "CliParser.h"
#include "Logger.h"
#include "sceneIO/SceneReaderFactory.h"
#include "utils/CraygMain.h"
#include "utils/FileSystemUtils.h"
#include <CraygInfo.h>
#include <image/io/ImageWriter.h>
#include <image/io/ImageWriters.h>
#include <iostream>
#include <renderer/Renderer.h>
#include <scene/Scene.h>
#include <utils/ImagePathResolver.h>

namespace crayg {

int craygMain(int argc, char *argv[]) {
    CliParser cliParser("crayg-standalone", argc, argv);
    CliParseResult parseResult = cliParser.parse();

    if (!parseResult.isValid()) {
        std::cout << (*parseResult.error) << std::endl;
        exit(1);
    }

    ImagePathResolver imagePathResolver;
    std::string imageOutputPath = imagePathResolver.resolve(parseResult.args->imageOutputPath);
    std::string logFilePath = FileSystemUtils::swapFileExtension(imageOutputPath, "txt");
    Logger::logToFile(logFilePath);

    Logger::info("Crayg Renderer version {}, commit {}", CraygInfo::VERSION, CraygInfo::COMMIT_HASH);

    Scene scene;

    std::string scenePath = parseResult.args->scenePath;
    SceneReader::ReadOptions readOptions;
    readOptions.cameraName = parseResult.args->cameraName;
    auto sceneReader = SceneReaderFactory::createSceneReader(scenePath, scene, readOptions);
    sceneReader->read();

    scene.renderSettings = parseResult.args->cliRenderSettingsOverride.resolveOverrides(scene.renderSettings);

    Image myImage(scene.renderSettings.resolution);

    ImageOutputDriver imageOutputDriver(myImage);

    Renderer renderer(scene, imageOutputDriver);
    renderer.renderScene();

    Logger::info("Writing image to {}..", imageOutputPath);
    ImageWriters::writeImage(myImage, imageOutputPath);
    Logger::info("Writing image done.");

    return 0;
}

}

int main(int argc, char *argv[]) {
    CRAYG_MAIN_IMPL;
}
