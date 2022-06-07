#include <scene/Scene.h>
#include <image/ImageWriter.h>
#include <Renderer.h>
#include <image/ImageWriters.h>
#include <CraygInfo.h>
#include <utils/ImagePathResolver.h>
#include <iostream>
#include "sceneIO/SceneReaderFactory.h"
#include "CliParser.h"
#include "Logger.h"

int main(int argc, char *argv[]) {
    crayg::Logger::initialize();
    try {
        crayg::CliParser cliParser("crayg-standalone", argc, argv);
        crayg::CliParseResult parseResult = cliParser.parse();

        if (!parseResult.isValid()) {
            std::cout << (*parseResult.error) << std::endl;
            exit(1);
        }

        crayg::Logger::info("Crayg Renderer version {}, commit {}",
                            crayg::CraygInfo::VERSION,
                            crayg::CraygInfo::COMMIT_HASH);

        crayg::Scene scene;

        std::string scenePath = parseResult.args->scenePath;
        crayg::SceneReader::ReadOptions readOptions;
        readOptions.cameraName = parseResult.args->cameraName;
        auto sceneReader = crayg::SceneReaderFactory::createSceneReader(scenePath, scene, readOptions);
        sceneReader->read();

        scene.renderSettings = parseResult.args->cliRenderSettingsOverride.resolveOverrides(scene.renderSettings);

        crayg::Image myImage(scene.renderSettings.resolution);

        crayg::ImageOutputDriver imageOutputDriver(myImage);

        crayg::Renderer renderer(scene, imageOutputDriver);
        renderer.renderScene();

        crayg::ImagePathResolver imagePathResolver;
        std::string imageOutputPath = imagePathResolver.resolve(parseResult.args->imageOutputPath);
        crayg::Logger::info("writing image to {}..", imageOutputPath);
        crayg::ImageWriters::writeImage(myImage, imageOutputPath);
        crayg::Logger::info("writing image done.");

        return 0;
    }
    catch (std::exception &e) {
        crayg::Logger::error("Caught exception: {}", e.what());
        return -1;
    }
}
