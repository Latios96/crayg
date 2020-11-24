
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
#include <utils/ImagePathResolver.h>

int main(int argc, char **argv) {
    crayg::Logger::initialize();
    try {
        QApplication a(argc, argv);

        crayg::CliParser cliParser(argc, argv);
        crayg::CliParseResult parseResult = cliParser.parse();

        if (!parseResult.isValid()) {
            spdlog::error(*parseResult.error);
            exit(1);
        }

        crayg::Logger::info("Crayg Renderer version {}, commit {}",
                            crayg::CraygInfo::VERSION,
                            crayg::CraygInfo::COMMIT_HASH);

        crayg::Scene scene;

        std::string scenePath = parseResult.args->scenePath;
        auto sceneReader = crayg::SceneReaderFactory::createSceneWriter(scenePath, scene);
        sceneReader->read();

        crayg::Image myImage(scene.renderSettings.resolution);

        auto imageWidget = new crayg::ImageWidget(scene.renderSettings.resolution);
        crayg::ImageWidgetOutputDriver imageWidgetOutputDriver(*imageWidget);
        crayg::FrameBufferWidget frameBufferWidget(*imageWidget);
        frameBufferWidget.show();

        crayg::Image image(scene.renderSettings.resolution);
        crayg::ImageOutputDriver imageOutputDriver(image);
        crayg::TeeOutputDriver teeOutputDriver(imageOutputDriver, imageWidgetOutputDriver);

        crayg::Renderer renderer(scene, teeOutputDriver);

        std::thread renderThread([&parseResult, &image, &renderer]() {
            renderer.renderScene();

            crayg::ImagePathResolver imagePathResolver;
            std::string imageOutputPath = imagePathResolver.resolve(parseResult.args->imageOutputPath);
            crayg::Logger::info("writing image to {}..", imageOutputPath);
            crayg::ImageWriters::writeImage(image, imageOutputPath);
            crayg::Logger::info("writing image done.");
        });
        renderThread.detach();

        return QApplication::exec();
    }
    catch (std::exception &e) {
        crayg::Logger::error("Caught exception: {}", e.what());
        return -1;
    }
}