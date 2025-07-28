#include "qtcrayg/foundation/QtBase.h"
#include "qtcrayg/foundation/QtMetaTypes.h"
#include "widgets/FrameBufferWidget.h"
#include <QtWidgets/qapplication.h>

#include "CraygInfo.h"
#include "Initialization.h"
#include "Logger.h"
#include "crayg_standalone/cli/CliParser.h"
#include "image/film/io/FilmWriter.h"
#include "image/imageiterators/buckets/ImageBucketSequences.h"
#include "image/imageiterators/pixels/ImageIterators.h"
#include "qtcrayg/resources/StyleSheetLoader.h"
#include "qtcrayg/utils/QtUtils.h"
#include "renderer/FlareRenderer.h"
#include "sceneIO/SceneReaderFactory.h"
#include "utils/CraygMain.h"
#include "utils/FileSystemUtils.h"
#include "utils/TextureStats.h"
#include "utils/tracing/CraygTracing.h"
#include "widgets/GuiTaskReporter.h"
#include "widgets/NextGenImageWidget.h"
#include "widgets/NextGenImageWidgetOutputDriver.h"

#include "image/io/ImageWriter.h"
#include "image/io/ImageWriters.h"
#include "renderer/Renderer.h"
#include "scene/Scene.h"
#include "utils/ImagePathResolver.h"
#include <QResource>
#include <tbb/task_group.h>
#include <thread>

namespace crayg {

int craygMain(int argc, char **argv) {
    QApplication application(argc, argv);
    StyleSheetLoader styleSheetLoader(StyleSheetLoader::Mode::EMBEDDED, application);
    styleSheetLoader.loadAndApply();

    registerQMetaTypes();

    CliParser cliParser("crayg-flarerenderer-gui", argc, argv);
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

    Logger::info("Crayg FlareRenderer version {}, commit {}", CraygInfo::VERSION, CraygInfo::COMMIT_HASH);

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

    FlareRenderer flareRenderer(scene, nextGenImageWidgetOutputDriver, taskReporter);
    flareRenderer.initialize();

    std::thread renderThread([&flareRenderer, &nextGenImageWidgetOutputDriver]() {
        try {
            flareRenderer.renderScene();
        } catch (std::exception &e) {
            Logger::error("Caught exception: {}", e.what());
        }
        FilmWriter::writeFilm(nextGenImageWidgetOutputDriver.getFilm(), "filmWriteTest.exr"); // todo take from cli
    });
    renderThread.detach();

    return QApplication::exec();
}

}

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(resources);
    CRAYG_MAIN_IMPL;
}