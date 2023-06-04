#include "QtBase.h"
#include "widgets/FrameBufferWidget.h"
#include "widgets/QtMetaTypes.h"
#include <QtWidgets/qapplication.h>

#include "CliParser.h"
#include "CraygInfo.h"
#include "Logger.h"
#include "resources/Stylesheet.h"
#include "sceneIO/SceneReaderFactory.h"
#include "utils/FileSystemUtils.h"
#include "widgets/ImageWidgetOutputDriver.h"
#include <image/io/ImageWriter.h>
#include <image/io/ImageWriters.h>
#include <outputdrivers/TeeOutputDriver.h>
#include <renderer/Renderer.h>
#include <scene/Scene.h>
#include <thread>
#include <utils/ImagePathResolver.h>

int main(int argc, char **argv) {
    crayg::Logger::initialize();
    try {
        QApplication a(argc, argv);
        a.setStyleSheet(STYLESHEET);

        registerQMetaTypes();

        crayg::CliParser cliParser("crayg-standalone-gui", argc, argv);
        crayg::CliParseResult parseResult = cliParser.parse();

        if (!parseResult.isValid()) {
            std::cout << (*parseResult.error) << std::endl;
            exit(1);
        }

        crayg::ImagePathResolver imagePathResolver;
        std::string imageOutputPath = imagePathResolver.resolve(parseResult.args->imageOutputPath);
        std::string logFilePath = crayg::FileSystemUtils::swapFileExtension(imageOutputPath, "txt");
        crayg::Logger::logToFile(logFilePath);

        crayg::Logger::info("Crayg Renderer version {}, commit {}", crayg::CraygInfo::VERSION,
                            crayg::CraygInfo::COMMIT_HASH);

        crayg::Scene scene;

        std::string scenePath = parseResult.args->scenePath;
        crayg::SceneReader::ReadOptions readOptions;
        readOptions.cameraName = parseResult.args->cameraName;
        auto sceneReader = crayg::SceneReaderFactory::createSceneReader(scenePath, scene, readOptions);
        sceneReader->read();

        scene.renderSettings = parseResult.args->cliRenderSettingsOverride.resolveOverrides(scene.renderSettings);

        crayg::Image image(scene.renderSettings.resolution);
        auto imageWidget = new crayg::ImageWidget(image);
        crayg::ImageWidgetOutputDriver imageWidgetOutputDriver(*imageWidget);
        crayg::FrameBufferWidget frameBufferWidget(*imageWidget);
        frameBufferWidget.show();

        QObject::connect(&imageWidgetOutputDriver.qtSignalAdapter, &crayg::QtSignalAdapter::metadataWritten,
                         &frameBufferWidget, &crayg::FrameBufferWidget::setImageMetadata);

        QObject::connect(&imageWidgetOutputDriver.qtSignalAdapter, &crayg::QtSignalAdapter::initialized,
                         &frameBufferWidget, &crayg::FrameBufferWidget::setImageSpec);

        QObject::connect(&frameBufferWidget, &crayg::FrameBufferWidget::channelChanged, imageWidget,
                         &crayg::ImageWidget::changeChannel);

        crayg::ImageOutputDriver imageOutputDriver(image);
        crayg::TeeOutputDriver teeOutputDriver(imageOutputDriver, imageWidgetOutputDriver);

        crayg::Renderer renderer(scene, teeOutputDriver);

        std::thread renderThread([&image, &renderer, &imageOutputPath]() {
            try {
                renderer.renderScene();

                crayg::Logger::info("Writing image to {}..", imageOutputPath);
                crayg::ImageWriters::writeImage(image, imageOutputPath);
                crayg::Logger::info("Writing image done.");
            } catch (std::exception &e) {
                crayg::Logger::error("Caught exception: {}", e.what());
            }
        });
        renderThread.detach();

        return QApplication::exec();
    }

    catch (std::exception &e) {
        crayg::Logger::backtrace();
        crayg::Logger::error("Caught exception: {}", e.what());
        return -1;
    }
}