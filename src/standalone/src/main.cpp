#include <scene/Scene.h>
#include <image/ImageWriter.h>
#include <Renderer.h>
#include <image/ImageWriters.h>
#include "sceneIO/SceneReaderFactory.h"
#include "CliParser.h"
#include "Logger.h"

const std::string VERSION = "1.4.0"; // todo move version to c

int main(int argc, char *argv[]) {
    Logger::initialize();
    CliParser cliParser(argc, argv);
    CliParseResult parseResult = cliParser.parse();

    if (!parseResult.isValid()) {
        spdlog::error(*parseResult.error);
        exit(1);
    }

    Logger::info("Crayg Renderer version {}", VERSION);

    Image myImage(800, 600);

    Scene scene;

    // read scene
    std::string scenePath = parseResult.args->scenePath;
    auto sceneReader = SceneReaderFactory::createSceneWriter(scenePath, scene);
    sceneReader->read();

    ImageOutputDriver imageOutputDriver(myImage);

    Renderer renderer(scene, myImage.getResolution(), imageOutputDriver);
    renderer.renderScene();

    Logger::info("writing image..");
    ImageWriters::writeImage(myImage, parseResult.args->imageOutputPath);

    Logger::info("writing image done.");
    return 0;
}
