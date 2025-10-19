#include "Renderer.h"
#include "GeometryCompiler.h"
#include "ImageMetadataCollector.h"
#include "SampleAccumulator.h"
#include "crayg/foundation/areaiterators/tiles/TileSequence.h"
#include "crayg/foundation/areaiterators/tiles/TileSequences.h"
#include "crayg/foundation/areaiterators/tiles/tilequeues/TileQueue.h"
#include "crayg/foundation/logging/Logger.h"
#include "crayg/foundation/physics/Wavelengths.h"
#include "crayg/foundation/progress/StopWatch.h"
#include "crayg/foundation/progress/TaskReporter.h"
#include "crayg/foundation/tracing/CraygTracing.h"
#include "crayg/image/ImageAlgorithms.h"
#include "crayg/image/ImageTile.h"
#include "crayg/renderer/tilesamplers/TileSamplerFactory.h"
#include "crayg/scene/camera/CameraModelFactory.h"
#include "integrators/IntegratorFactory.h"
#include "integrators/RaytracingIntegrator.h"
#include "intersectors/IntersectorFactory.h"
#include "sampling/Random.h"
#include <Imath/half.h>
#include <memory>
#include <numeric>
#include <tbb/task_group.h>
#include <variant>

namespace crayg {

Renderer::Renderer(Scene &scene, NextGenOutputDriver &outputDriver, BaseTaskReporter &taskReporter,
                   TileQueue &tileQueue)
    : scene(scene), outputDriver(outputDriver), taskReporter(taskReporter), tileQueue(tileQueue) {
}

void Renderer::renderScene() {
    init();
    Logger::info("Starting rendering..");

    initTiles();

    auto taskProgressController = taskReporter.startTask("Rendering", tileSequence.size());

    bool serialRendering = false;
    if (serialRendering) {
        renderSerial(taskProgressController);
    } else {
        renderParallel(taskProgressController);
    }

    Logger::info("Rendering done.");

    const auto renderTime = taskProgressController.finish();
    writeImageMetadata(renderTime);

    tileStats.processTileTimes(outputDriver, scene.renderSettings.resolution);
}

void Renderer::renderParallel(BaseTaskReporter::TaskProgressController &taskProgressController) {
    CRAYG_TRACE_SCOPE("Renderer");
    tileQueue.start(tileSequence);
    tbb::task_group task_group;

    for (unsigned int i = 0; i < std::thread::hardware_concurrency(); i++) {
        task_group.run([&taskProgressController, this]() {
            while (true) {
                const auto tile = tileQueue.nextTile();
                if (!tile) {
                    return;
                }
                renderTile(*tile);
                taskProgressController.iterationDone();
            }
        });
    }
    task_group.wait();
}

void Renderer::renderSerial(BaseTaskReporter::TaskProgressController &taskProgressController) {
    CRAYG_TRACE_SCOPE("Renderer");
    tileQueue.start(tileSequence);
    while (true) {
        const auto tile = tileQueue.nextTile();
        if (!tile) {
            return;
        }
        renderTile(*tile);
        taskProgressController.iterationDone();
    }
}

void Renderer::renderTile(const Tile &tile) {
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    outputDriver.startTile(tile);

    tileSampler->sampleTile(tile);
    tileStats.processTileTime(outputDriver.getFilm(), tile, startTime);

    outputDriver.finishTile(tile);
}

void Renderer::init() {
    CRAYG_TRACE_SCOPE("Renderer");

    {
        InformativeScopedStopWatch initializeCamera("Initialize camera");
        cameraModel = CameraModelFactory::createCameraModel(*scene.camera, scene.renderSettings.resolution);
        cameraModel->init(taskReporter);
    }

    GeometryCompiler geometryCompiler(scene, taskReporter);
    geometryCompiler.compile();
    Logger::info("Objects in scene: {:L}", scene.objects.size());
    Logger::info("Primitives in scene: {:L}", scene.primitiveCount());

    auto progressController = taskReporter.startTask("Building SceneIntersector", 1);
    sceneIntersector = IntersectorFactory::createSceneIntersector(scene.renderSettings.intersectorType, scene);
    integrator = std::unique_ptr<AbstractIntegrator>(IntegratorFactory::createIntegrator(
        scene.renderSettings.integratorType, scene, sceneIntersector, scene.renderSettings.integratorSettings));
    progressController.finish();
}

void Renderer::initOutputDriver() {
    tileSampler = TileSamplerFactory::createTileSampler(scene.renderSettings,
                                                        [this](Vector2f samplePos) { return renderSample(samplePos); });

    ImageSpec imageSpec = requiredImageSpec(scene.renderSettings.resolution);

    FilmSpecBuilder filmSpecBuilder(scene.renderSettings.resolution, FilmBufferType::VALUE, PixelFormat::FLOAT32);

    for (auto &channel : imageSpec.channels) {
        if (channel.name == "rgb") {
            continue;
        }
        FilmBufferSpec filmBufferSpec{channel.name, FilmBufferType::VALUE, channel.pixelFormat,
                                      channel.colorChannelCount};
        filmSpecBuilder.addChannel(filmBufferSpec);
    }

    if (scene.renderSettings.regionToRender) {
        filmSpecBuilder.addRenderRegion(*scene.renderSettings.regionToRender);
    }

    outputDriver.initialize(filmSpecBuilder.finish());
    tileSampler->setFilm(outputDriver.getFilm());
}

void Renderer::initTiles() {
    if (!scene.renderSettings.regionToRender) {
        tileSequence =
            TileSequences::getSequence(scene.renderSettings.resolution, 8, scene.renderSettings.tileSequenceType);
        return;
    }

    PixelRegion pixelRegion = scene.renderSettings.regionToRender->toPixelRegion(scene.renderSettings.resolution);
    Logger::info("Cropping rendered region to {}", pixelRegion);
    auto tiles = TileSequences::getSequence(pixelRegion, 8, scene.renderSettings.tileSequenceType);

    for (auto &tile : tiles) {
        tile = Tile(tile.getPosition() + pixelRegion.min, tile.getWidth(), tile.getHeight());
    }
    tileSequence = tiles;
}

Color Renderer::renderSample(const Vector2f &samplePos) {
    if (scene.renderSettings.useSpectralLensing) {
        const float r = renderSample(samplePos, WavelengthsRgb::R).r;
        const float g = renderSample(samplePos, WavelengthsRgb::G).g;
        const float b = renderSample(samplePos, WavelengthsRgb::B).b;
        return {r, g, b};
    }
    return renderSample(samplePos, FraunhoferLines::SODIUM.wavelength);
}

Color Renderer::renderSample(const Vector2f &samplePos, float waveLength) {
    auto rayWithWeight = cameraModel->createPrimaryRay(samplePos, waveLength);
    if (!rayWithWeight.ray) {
        return Color::createBlack();
    }
    return integrator->integrate(*rayWithWeight.ray, 0, RayType::CAMERA) * rayWithWeight.weight;
}

void Renderer::writeImageMetadata(std::chrono::seconds renderTime) {
    ImageMetadataCollector imageMetadataCollector(renderTime, &scene);

    ImageMetadata imageMetadata = imageMetadataCollector.collectMetadata();

    outputDriver.getFilm().metadata = imageMetadata;
    outputDriver.updateImageMetadata();
}

ImageSpec Renderer::requiredImageSpec(const Resolution &resolution) const {
    ImageSpecBuilder builder(resolution);
    if (scene.renderSettings.regionToRender) {
        builder.addRenderRegion(*scene.renderSettings.regionToRender);
    }
    tileSampler->addRequiredImageSpecs(builder);
    builder.createGreyFloatChannel("absoluteRenderTime");
    builder.createRgbFloatChannel("relativeRenderTime");
    return builder.finish();
}

}
