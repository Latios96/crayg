
#include <QtWidgets/qapplication.h>
#include "FrameBufferWidget.h"

#include <scene/Scene.h>
#include <image/ImageWriter.h>
#include <Renderer.h>
#include <image/ImageWriters.h>
#include "sceneIO/SceneReaderFactory.h"
#include "CliParser.h"
#include "Logger.h"
#include "ImageWidgetOutputDriver.h"

const std::string VERSION = "1.4.0"; // todo move version to c

int main(int argc, char **argv) {
    QApplication a(argc, argv);
    Logger::initialize();

    CliParser cliParser(argc, argv);
    CliParseResult parseResult = cliParser.parse();

    if (!parseResult.isValid()) {
        spdlog::error(*parseResult.error);
        exit(1);
    }

    Logger::info("Crayg Renderer version {}", VERSION);

    Scene scene;

    std::string scenePath = parseResult.args->scenePath;
    auto sceneReader = SceneReaderFactory::createSceneWriter(scenePath, scene);
    sceneReader->read();

    Image myImage(scene.renderSettings.resolution);

    auto imageWidget = new ImageWidget(scene.renderSettings.resolution);
    ImageWidgetOutputDriver imageWidgetOutputDriver(*imageWidget);

    FrameBufferWidget frameBufferWidget(*imageWidget);
    frameBufferWidget.show();

    Renderer renderer(scene, imageWidgetOutputDriver);

    std::thread t1([&renderer, &myImage, &parseResult]() {
        renderer.renderScene();

        Logger::info("writing image..");
        ImageWriters::writeImage(myImage, parseResult.args->imageOutputPath);
        Logger::info("writing image done.");
    });
    t1.detach();

    return QApplication::exec();
}