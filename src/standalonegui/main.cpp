
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
#include "CraygInfo.h"
#include <thread>
#include <image/TeeOutputDriver.h>
#include <ImagePathResolver.h>

int main(int argc, char **argv) {
    Logger::initialize();
    try {
        QApplication a(argc, argv);

        crayg::CliParser cliParser(argc, argv);
        crayg::CliParseResult parseResult = cliParser.parse();

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

        auto imageWidget = new crayg::ImageWidget(scene.renderSettings.resolution);
        crayg::ImageWidgetOutputDriver imageWidgetOutputDriver(*imageWidget);
        crayg::FrameBufferWidget frameBufferWidget(*imageWidget);
        frameBufferWidget.show();

        Image image(scene.renderSettings.resolution);
        ImageOutputDriver imageOutputDriver(image);
        TeeOutputDriver teeOutputDriver(imageOutputDriver, imageWidgetOutputDriver);

        Renderer renderer(scene, teeOutputDriver);

        std::thread renderThread([&parseResult, &image, &renderer]() {
            renderer.renderScene();

            ImagePathResolver imagePathResolver;
            std::string imageOutputPath = imagePathResolver.resolve(parseResult.args->imageOutputPath);
            Logger::info("writing image to {}..", imageOutputPath);
            ImageWriters::writeImage(image, imageOutputPath);
            Logger::info("writing image done.");
        });
        renderThread.detach();

        return QApplication::exec();
    }
    catch (std::exception &e) {
        Logger::error("Caught exception: {}", e.what());
        return -1;
    }
}