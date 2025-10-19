// clang-format off
#include <QResource>
#include <QtWidgets/qapplication.h>
// clang-format on
#include "CraygInfo.h"
#include "Initialization.h"
#include "crayg/foundation/executable/CraygMain.h"
#include "crayg/foundation/filesystem/FileAsString.h"
#include "crayg/foundation/logging/Logger.h"
#include "crayg/foundation/progress/StopWatch.h"
#include "crayg/foundation/tracing/CraygTracing.h"
#include "craygstandalone/cli/CliParser.h"
#include "craygstandalonegui/widgets/framebuffer/FrameBufferWidget.h"
#include "craygstandalonegui/widgets/framebuffer/NextGenImageWidget.h"
#include "craygstandalonegui/widgets/framebuffer/NextGenImageWidgetOutputDriver.h"
#include "craygstandalonegui/widgets/taskreporter/GuiTaskReporter.h"
#include "image/io/imageformatwriters/ImageFormatWriteOptions.h"
#include "image/io/imageformatwriters/ImageFormatWriters.h"
#include "qtcrayg/foundation/QtBase.h"
#include "qtcrayg/foundation/QtMetaTypes.h"
#include "qtcrayg/resources/StyleSheetLoader.h"
#include "qtcrayg/utils/QtUtils.h"
#include "renderer/Renderer.h"
#include "renderer/TextureStats.h"
#include "scene/Scene.h"
#include "sceneIO/SceneReaderFactory.h"
#include "utils/ImagePathResolver.h"
#include <thread>

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

    const std::filesystem::path imageOutputPath = ImagePathResolver::resolve(parseResult.args->imageOutputPath);
    const std::filesystem::path logFilePath = std::filesystem::path(imageOutputPath).replace_extension(".txt");
    Logger::logToFile(logFilePath);
    CRAYG_IF_TRACING_ENABLED({
        const std::filesystem::path traceFilePath = std::filesystem::path(imageOutputPath).replace_extension(".json");
        Logger::info("Tracing enabled, tracing to {}", traceFilePath);
        mtr_init(traceFilePath.string().c_str());
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