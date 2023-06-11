#include "QtBase.h"
#include "widgets/FrameBufferWidget.h"
#include "widgets/QtMetaTypes.h"
#include <QtWidgets/qapplication.h>

#include "CliParser.h"
#include "CraygInfo.h"
#include "Logger.h"
#include "resources/Stylesheet.h"
#include "sceneIO/SceneReaderFactory.h"
#include "utils/CraygMain.h"
#include "utils/FileSystemUtils.h"
#include "widgets/ImageWidgetOutputDriver.h"
#include <image/io/ImageWriter.h>
#include <image/io/ImageWriters.h>
#include <outputdrivers/TeeOutputDriver.h>
#include <renderer/Renderer.h>
#include <scene/Scene.h>
#include <thread>
#include <utils/ImagePathResolver.h>

namespace crayg {

int craygMain(int argc, char **argv) {
    QApplication a(argc, argv);
    a.setStyleSheet(STYLESHEET);

    registerQMetaTypes();

    CliParser cliParser("crayg-standalone-gui", argc, argv);
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

    Image image(scene.renderSettings.resolution);
    auto imageWidget = new ImageWidget(image);
    ImageWidgetOutputDriver imageWidgetOutputDriver(*imageWidget);
    FrameBufferWidget frameBufferWidget(*imageWidget);
    frameBufferWidget.show();

    QObject::connect(&imageWidgetOutputDriver.qtSignalAdapter, &QtSignalAdapter::metadataWritten, &frameBufferWidget,
                     &FrameBufferWidget::setImageMetadata);

    QObject::connect(&imageWidgetOutputDriver.qtSignalAdapter, &QtSignalAdapter::initialized, &frameBufferWidget,
                     &FrameBufferWidget::setImageSpec);

    QObject::connect(&frameBufferWidget, &FrameBufferWidget::channelChanged, imageWidget, &ImageWidget::changeChannel);

    ImageOutputDriver imageOutputDriver(image);
    TeeOutputDriver teeOutputDriver(imageOutputDriver, imageWidgetOutputDriver);

    Renderer renderer(scene, teeOutputDriver);

    std::thread renderThread([&image, &renderer, &imageOutputPath]() {
        try {
            renderer.renderScene();

            Logger::info("Writing image to {}..", imageOutputPath);
            ImageWriters::writeImage(image, imageOutputPath);
            Logger::info("Writing image done.");
        } catch (std::exception &e) {
            Logger::error("Caught exception: {}", e.what());
        }
    });
    renderThread.detach();

    return QApplication::exec();
}

}

int main(int argc, char *argv[]) {
    CRAYG_MAIN_IMPL;
}