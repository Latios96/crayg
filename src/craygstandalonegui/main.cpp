#include "craygstandalonegui/widgets/framebuffer/FrameBufferWidget.h"
#include "qtcrayg/foundation/QtBase.h"
#include "qtcrayg/foundation/QtMetaTypes.h"
#include <QtWidgets/qapplication.h>

#include "CraygInfo.h"
#include "Initialization.h"
#include "Logger.h"
#include "craygstandalone/cli/CliParser.h"
#include "craygstandalonegui/widgets/framebuffer/NextGenImageWidget.h"
#include "craygstandalonegui/widgets/framebuffer/NextGenImageWidgetOutputDriver.h"
#include "craygstandalonegui/widgets/taskreporter/GuiTaskReporter.h"
#include "image/io/imageformatwriters/ImageFormatWriteOptions.h"
#include "image/io/imageformatwriters/ImageFormatWriters.h"
#include "qtcrayg/resources/StyleSheetLoader.h"
#include "qtcrayg/utils/QtUtils.h"
#include "sceneIO/SceneReaderFactory.h"
#include "utils/CraygMain.h"
#include "utils/FileSystemUtils.h"
#include "utils/StopWatch.h"
#include "utils/TextureStats.h"
#include "utils/tracing/CraygTracing.h"
#include <QResource>

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

    TaskReporterQtSignalAdapter taskReporterQtSignalAdapter;
    GuiTaskReporter taskReporter(taskReporterQtSignalAdapter);
    Image image(scene.renderSettings.resolution);
    auto imageWidget = new NextGenImageWidget();
    NextGenImageWidgetOutputDriver nextGenImageWidgetOutputDriver(*imageWidget);
    FrameBufferWidget frameBufferWidget(*imageWidget);
    frameBufferWidget.show();

    QObject::connect(&nextGenImageWidgetOutputDriver, &NextGenImageWidgetOutputDriver::imageMetadataUpdated,
                     [&frameBufferWidget, &nextGenImageWidgetOutputDriver]() {
                         frameBufferWidget.setImageMetadata(nextGenImageWidgetOutputDriver.getFilm().metadata);
                     });
    QObject::connect(&nextGenImageWidgetOutputDriver, &NextGenImageWidgetOutputDriver::initialized,
                     [&frameBufferWidget, &nextGenImageWidgetOutputDriver]() {
                         frameBufferWidget.setFilmSpec(nextGenImageWidgetOutputDriver.getFilm().getFilmSpec());
                     });

    QObject::connect(&frameBufferWidget, &FrameBufferWidget::channelChanged, &nextGenImageWidgetOutputDriver,
                     &NextGenImageWidgetOutputDriver::processCurrentChannelChanged);

    QObject::connect(&taskReporterQtSignalAdapter, &TaskReporterQtSignalAdapter::taskStarted, &frameBufferWidget,
                     &FrameBufferWidget::startTask);
    QObject::connect(&taskReporterQtSignalAdapter, &TaskReporterQtSignalAdapter::taskFinished, &frameBufferWidget,
                     &FrameBufferWidget::finishTask);
    QObject::connect(&taskReporterQtSignalAdapter, &TaskReporterQtSignalAdapter::taskProgressUpdated,
                     &frameBufferWidget, &FrameBufferWidget::updateTask);

    const std::function<Vector2i()> getMousePosition = [imageWidget, &scene]() {
        auto point = imageWidget->mapFromGlobal(QCursor::pos());
        const int x = static_cast<float>(point.x()) / imageWidget->width() * scene.renderSettings.resolution.getWidth();
        const int y =
            static_cast<float>(point.y()) / imageWidget->height() * scene.renderSettings.resolution.getHeight();
        return Vector2i(x, y);
    };
    TileQueue tileQueue(getMousePosition);

    Renderer renderer(scene, nextGenImageWidgetOutputDriver, taskReporter, tileQueue);
    renderer.initOutputDriver();
    frameBufferWidget.connectToggleFollowMouse([&tileQueue]() { tileQueue.switchMode(); });

    std::thread renderThread([&nextGenImageWidgetOutputDriver, &renderer, &imageOutputPath, &scene]() {
        try {
            renderer.renderScene();

            TextureStats textureStats;
            Logger::info(textureStats.getTextureStats());

            Logger::info("Writing image to {}..", imageOutputPath);
            ImageFormatWriters::write(imageOutputPath, nextGenImageWidgetOutputDriver.getFilm(),
                                      scene.renderSettings.imageFormatWriteOptions);
            Logger::info("Writing image done.");

            CRAYG_IF_TRACING_ENABLED({
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