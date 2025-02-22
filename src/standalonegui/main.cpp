#include "qtcrayg/foundation/QtBase.h"
#include "qtcrayg/foundation/QtMetaTypes.h"
#include "widgets/FrameBufferWidget.h"
#include <QtWidgets/qapplication.h>

#include "CliParser.h"
#include "CraygInfo.h"
#include "Logger.h"
#include "qtcrayg/resources/StyleSheetLoader.h"
#include "qtcrayg/utils/QtUtils.h"
#include "sceneIO/SceneReaderFactory.h"
#include "utils/CraygMain.h"
#include "utils/FileSystemUtils.h"
#include "utils/TextureStats.h"
#include "utils/tracing/CraygTracing.h"
#include "widgets/GuiTaskReporter.h"
#include "widgets/ImageWidgetOutputDriver.h"
#include <QResource>
#include <image/io/ImageWriter.h>
#include <image/io/ImageWriters.h>
#include <outputdrivers/TeeOutputDriver.h>
#include <renderer/Renderer.h>
#include <scene/Scene.h>
#include <thread>
#include <utils/ImagePathResolver.h>

namespace crayg {

int craygMain(int argc, char **argv) {
    QApplication application(argc, argv);
    StyleSheetLoader styleSheetLoader(StyleSheetLoader::Mode::EMBEDDED, application);
    styleSheetLoader.loadAndApply();

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
    CRG_IF_TRACE({
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

    TaskReporterQtSignalAdapter taskReporterQtSignalAdapter;
    GuiTaskReporter taskReporter(taskReporterQtSignalAdapter);
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

    QObject::connect(&taskReporterQtSignalAdapter, &TaskReporterQtSignalAdapter::taskStarted, &frameBufferWidget,
                     &FrameBufferWidget::startTask);
    QObject::connect(&taskReporterQtSignalAdapter, &TaskReporterQtSignalAdapter::taskFinished, &frameBufferWidget,
                     &FrameBufferWidget::finishTask);
    QObject::connect(&taskReporterQtSignalAdapter, &TaskReporterQtSignalAdapter::taskProgressUpdated,
                     &frameBufferWidget, &FrameBufferWidget::updateTask);

    ImageOutputDriver imageOutputDriver(image);
    TeeOutputDriver teeOutputDriver(imageOutputDriver, imageWidgetOutputDriver);

    const std::function<Vector2i()> getMousePosition = [imageWidget, &scene]() {
        auto point = imageWidget->mapFromGlobal(QCursor::pos());
        const int x = static_cast<float>(point.x()) / imageWidget->width() * scene.renderSettings.resolution.getWidth();
        const int y =
            static_cast<float>(point.y()) / imageWidget->height() * scene.renderSettings.resolution.getHeight();
        return Vector2i(x, y);
    };
    BucketQueue bucketQueue(getMousePosition);

    Renderer renderer(scene, teeOutputDriver, taskReporter, bucketQueue);
    frameBufferWidget.connectToggleFollowMouse([&bucketQueue]() { bucketQueue.switchMode(); });

    std::thread renderThread([&image, &renderer, &imageOutputPath]() {
        try {
            renderer.renderScene();

            TextureStats textureStats;
            Logger::info(textureStats.getTextureStats());

            Logger::info("Writing image to {}..", imageOutputPath);
            ImageWriters::writeImage(image, imageOutputPath);
            Logger::info("Writing image done.");

            CRG_IF_TRACE({
                mtr_flush();
                Logger::info("Shutting down trace.");
                mtr_shutdown();
                Logger::info("Flushing trace.");
            });

        } catch (std::exception &e) {
            Logger::error("Caught exception: {}", e.what());
        }
    });
    renderThread.detach();

    return QApplication::exec();
}

}

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(resources);
    CRAYG_MAIN_IMPL;
}