#include <iostream>
#include "fmt/format.h"
#include <image/Image.h>
#include <scene/Scene.h>
#include <image/ImageWriter.h>
#include <image/ImageWriterFactory.h>
#include <intersectors/SceneIntersector.h>
#include <Renderer.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "sceneIO/SceneReaderFactory.h"
#include "CliParser.h"

const std::string VERSION = "1.4.0"; // todo move version to c

int main(int argc, char *argv[]) {
    CliParser cliParser(argc, argv);
    CliParseResult parseResult = cliParser.parse();

    if (!parseResult.isValid()) {
        spdlog::error(*parseResult.error);
        exit(1);
    }

    auto console = spdlog::stdout_color_mt("console");

    console->info("Crayg Renderer version {}", VERSION);

    Image myImage(800, 600);

    Scene scene;

    // read scene
    std::string scenePath = parseResult.args->scenePath;
    auto sceneReader = SceneReaderFactory::createSceneWriter(scenePath, scene);
    sceneReader->read();

    Renderer renderer(scene, myImage);
    renderer.renderScene();

    console->info("writing image..");
    std::unique_ptr<ImageWriter> imageWriter(createImageWriter(ImageWriterType::BMP));

    imageWriter->writeImage(myImage, parseResult.args->imageOutputPath);

    console->info("writing image done.");
    return 0;
}
