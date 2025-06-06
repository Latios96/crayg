#include "qtcrayg/foundation/QtBase.h"
#include "qtcrayg/foundation/QtMetaTypes.h"
#include "widgets/FrameBufferWidget.h"
#include <QtWidgets/qapplication.h>

#include "CliParser.h"
#include "CraygInfo.h"
#include "Logger.h"
#include "image/film/io/FilmWriter.h"
#include "image/imageiterators/buckets/ImageBucketSequences.h"
#include "image/imageiterators/pixels/ImageIterators.h"
#include "qtcrayg/resources/StyleSheetLoader.h"
#include "qtcrayg/utils/QtUtils.h"
#include "sceneIO/SceneReaderFactory.h"
#include "utils/CraygMain.h"
#include "utils/FileSystemUtils.h"
#include "utils/TextureStats.h"
#include "utils/tracing/CraygTracing.h"
#include "widgets/GuiTaskReporter.h"
#include "widgets/ImageWidgetOutputDriver.h"
#include "widgets/NextGenImageWidget.h"
#include "widgets/NextGenImageWidgetOutputDriver.h"

#include <QResource>
#include <image/io/ImageWriter.h>
#include <image/io/ImageWriters.h>
#include <outputdrivers/TeeOutputDriver.h>
#include <renderer/Renderer.h>
#include <scene/Scene.h>
#include <tbb/task_group.h>
#include <thread>
#include <utils/ImagePathResolver.h>

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
    CRG_IF_TRACE({
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
                         frameBufferWidget.setImageMetadata(nextGenImageWidgetOutputDriver.getFilm().getMetadata());
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
    BucketQueue bucketQueue(getMousePosition);

    frameBufferWidget.connectToggleFollowMouse([&bucketQueue]() { bucketQueue.switchMode(); });
    nextGenImageWidgetOutputDriver.initialize(FilmSpecBuilder(Resolution(1820, 720)).finish());

    auto buckets = ImageBucketSequences::getSequence(Resolution(1820, 720), 8, BucketSequenceType::HILBERT);
    bucketQueue.start(buckets);
    std::thread renderThread([&nextGenImageWidgetOutputDriver, &bucketQueue]() {
        try {
            while (true) {
                const auto imageBucket = bucketQueue.nextBucket();
                if (!imageBucket) {
                    break;
                }
                nextGenImageWidgetOutputDriver.startBucket(*imageBucket);
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                for (int i = 0; i < 3; i++) {
                    Color color = Color::createRandom();
                    for (auto pixel : ImageIterators::lineByLine(*imageBucket)) {
                        nextGenImageWidgetOutputDriver.getFilm().addSample("rgb", imageBucket->getPosition() + pixel,
                                                                           color);
                    }
                    nextGenImageWidgetOutputDriver.updateAllChannelsInBucket(*imageBucket);
                    std::this_thread::sleep_for(std::chrono::milliseconds(250));
                }
                nextGenImageWidgetOutputDriver.finishBucket(*imageBucket);
            }
        } catch (std::exception &e) {
            Logger::error("Caught exception: {}", e.what());
        }
        FilmWriter::writeFilm(nextGenImageWidgetOutputDriver.getFilm(), "filmWriteTest.exr");
    });
    renderThread.detach();

    return QApplication::exec();
}

}

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(resources);
    CRAYG_MAIN_IMPL;
}