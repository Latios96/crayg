#include <scene/Scene.h>
#include <image/ImageWriter.h>
#include <Renderer.h>
#include <image/ImageWriters.h>
#include <CraygInfo.h>
#include "sceneIO/SceneReaderFactory.h"
#include "CliParser.h"
#include "Logger.h"

int main(int argc, char *argv[]) {
    Logger::initialize();
    try {
        CliParser cliParser(argc, argv);
        CliParseResult parseResult = cliParser.parse();

        if (!parseResult.isValid()) {
            spdlog::error(*parseResult.error);
            exit(1);
        }

        Logger::info("Crayg Renderer version {}, commit {}", CraygInfo::VERSION, CraygInfo::COMMIT_HASH);

        Scene scene;

        std::string scenePath = parseResult.args->scenePath;
        auto sceneReader = SceneReaderFactory::createSceneWriter(scenePath, scene);
        sceneReader->read();

        Image myImage(scene.renderSettings.resolution);

        ImageOutputDriver imageOutputDriver(myImage);

        Renderer renderer(scene, imageOutputDriver);
        renderer.renderScene();

        Logger::info("writing image..");
        ImageWriters::writeImage(myImage, parseResult.args->imageOutputPath);

        Logger::info("writing image done.");
        return 0;
    }
    catch (std::exception &e) {
        Logger::error("Caught exception: {}", e.what());
        return -1;
    }
}
