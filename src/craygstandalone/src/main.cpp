#include "Initialization.h"
#include "Logger.h"
#include "craygstandalone/cli/CliParser.h"
#include "image/film/io/FilmWriter.h"
#include "image/io/imageformatwriters/ImageFormatWriters.h"
#include "sceneIO/SceneReaderFactory.h"
#include "utils/CraygMain.h"
#include "utils/FileSystemUtils.h"
#include "utils/TextureStats.h"
#include "utils/tracing/CraygTracing.h"
#include <CraygInfo.h>
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
    CRAYG_IF_TRACING_ENABLED({
        std::string traceFilePath = FileSystemUtils::swapFileExtension(imageOutputPath, "json");
        Logger::info("Tracing enabled, tracing to {}", traceFilePath);
        mtr_init(traceFilePath.c_str());
    });

    Logger::info("Crayg Renderer version {}, commit {}", CraygInfo::VERSION, CraygInfo::COMMIT_HASH);

    Scene scene;

    std::string scenePath = parseResult.args->scenePath;
    SceneReader::ReadOptions readOptions;
    readOptions.cameraName = parseResult.args->cameraName;
    readOptions.variantSelections = parseResult.args->variantSelections;
    auto sceneReader = SceneReaderFactory::createSceneReader(scenePath, scene, readOptions);
    sceneReader->read();

    scene.renderSettings = parseResult.args->cliRenderSettingsOverride.resolveOverrides(scene.renderSettings);

    Image myImage(scene.renderSettings.resolution);

    NextGenOutputDriver outputDriver;

    TaskReporter taskReporter;
    BucketQueue bucketQueue([]() { return Vector2i(); });
    Renderer renderer(scene, outputDriver, taskReporter, bucketQueue);
    renderer.initOutputDriver();
    renderer.renderScene();

    TextureStats textureStats;
    Logger::info(textureStats.getTextureStats());

    Logger::info("Writing image to {}..", imageOutputPath);
    ImageFormatWriters::write(imageOutputPath, outputDriver.getFilm(), scene.renderSettings.imageFormatWriteOptions);
    Logger::info("Writing image done.");

    CRAYG_IF_TRACING_ENABLED({
        mtr_flush();
        Logger::info("Shutting down trace.");
        mtr_shutdown();
        Logger::info("Flushing trace.");
    });

    return 0;
}

}

int main(int argc, char *argv[]) {
    CRAYG_MAIN_IMPL;
}
