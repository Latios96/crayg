#include "FlareRenderer.h"
#include "sampling/Sampling.h"
#include "scene/camera/realistic/Wavelengths.h"
#include "scene/lights/AreaLight.h"
#include <tbb/parallel_for.h>

namespace crayg {

FlareRenderer::FlareRenderer(Scene &scene, NextGenOutputDriver &outputDriver, BaseTaskReporter &taskReporter)
    : scene(scene), outputDriver(outputDriver), taskReporter(taskReporter) {
}

struct FlareRay {
    Ray ray;
    Color intensity;
    float lambda;
};

CRAYG_DTO_2(ReflectionEvent, int, indexFirstReflection, int, indexLastReflection);

std::vector<ReflectionEvent> createReflectionSequences(const CameraLens &cameraLens) {
    const int totalSequenceCount = cameraLens.surfaces.size() * (cameraLens.surfaces.size() - 2) / 2;
    std::vector<ReflectionEvent> sequences;
    sequences.reserve(totalSequenceCount);
    for (int firstIndex = 0; firstIndex < cameraLens.surfaces.size(); firstIndex++) {
        for (int lastIndex = cameraLens.surfaces.size() - 1; lastIndex > firstIndex; lastIndex--) {
            const bool involvesAperture =
                cameraLens.surfaces[firstIndex].isAperture() || cameraLens.surfaces[lastIndex].isAperture();
            if (involvesAperture) {
                continue;
            }
            sequences.emplace_back(lastIndex, firstIndex);
        }
    }
    return sequences;
}

void trace(std::shared_ptr<Light> &light, float firstSurfaceApertureRadius, Camera &camera, CameraLens &cameraLens,
           const std::vector<ReflectionEvent> &reflectionEvents, const Bounds2df &filmPhysicalExtend, float pixelSize,
           int samplesPerLight, BaseTaskReporter::TaskProgressController &progressController, Film &film,
           const Resolution &resolution) {

    Vector3f pointOnLightSource = light->getPosition();
    const bool isAreaLight = light->getType() == "RectLight" || light->getType() == "DiskLight";
    if (isAreaLight) {
        auto areaLight = std::dynamic_pointer_cast<AreaLight>(light);
        pointOnLightSource = areaLight->sampleLightShape();
    }
    const Vector2f pointOnFirstSurface2d = Sampling::concentricSampleDisk() * firstSurfaceApertureRadius;
    // todo measure how this can be improved by sampling the unit disk (at least for spherical front elements)
    // const Vector2f pointOnFirstSurface2d = Sampling::concentricSampleDisk() *
    // cameraLens.getFirstSurface().apertureRadius;

    Vector3f pointOnFirstSurface = Vector3f(pointOnFirstSurface2d.x, pointOnFirstSurface2d.y,
                                            cameraLens.getSurfaceCenter(cameraLens.getFirstSurface()));
    pointOnFirstSurface = camera.getTransform().applyForPoint(pointOnFirstSurface);

    // todo estimate radiance to camera lens
    // todo abort if there is no radiance
    // todo abort if light is occluded by geometry

    // todo extract and test this
    size_t reflectionEventIndex = static_cast<size_t>(Random::random() * reflectionEvents.size());
    if (reflectionEventIndex >= reflectionEvents.size()) {
        reflectionEventIndex = reflectionEvents.size() - 1;
    }
    const ReflectionEvent &reflectionEvent = reflectionEvents[reflectionEventIndex];

    FlareRay flareRay;
    flareRay.ray = Ray(pointOnLightSource, (pointOnFirstSurface - pointOnLightSource).normalize());
    flareRay.ray = camera.getTransform().applyInverse(flareRay.ray);
    // flareRay.ray = Ray({0, 0, 25}, {0, 0, -1});
    flareRay.ray.startPoint.z = -flareRay.ray.startPoint.z;
    flareRay.ray.direction.z = -flareRay.ray.direction.z;
    flareRay.intensity = light->getColor() * light->getIntensity();
    // flareRay.lambda = FraunhoferLines::SODIUM.wavelength;

    const float wavelengthSample = 1;
    if (wavelengthSample < 0.33f) {
        flareRay.lambda = WavelengthsRgb::R;
        flareRay.intensity.g = 0;
        flareRay.intensity.b = 0;

    } else if (wavelengthSample < 0.66f) {
        flareRay.lambda = WavelengthsRgb::G;
        flareRay.intensity.r = 0;
        flareRay.intensity.b = 0;
    } else {
        flareRay.lambda = WavelengthsRgb::B;
        flareRay.intensity.r = 0;
        flareRay.intensity.g = 0;
    }

    Vector3f surfaceNormal;
    auto maybeRay = cameraLens.traceUntil(flareRay.ray, 0, reflectionEvent.indexFirstReflection, 1, flareRay.lambda,
                                          &surfaceNormal);

    if (!maybeRay) {
        return;
    }
    flareRay.ray = *maybeRay;

    flareRay.ray.direction = flareRay.ray.direction.reflect(surfaceNormal);
    flareRay.intensity = flareRay.intensity * 0.01; // todo use proper Fresnel/Schlick

    maybeRay = cameraLens.traceUntil(flareRay.ray, reflectionEvent.indexFirstReflection - 1,
                                     reflectionEvent.indexLastReflection, -1, flareRay.lambda, &surfaceNormal);
    if (!maybeRay) {
        return;
    }
    flareRay.ray = *maybeRay;

    flareRay.ray.direction = flareRay.ray.direction.reflect(surfaceNormal);
    flareRay.intensity = flareRay.intensity * 0.01; // todo use proper Fresnel/Schlick

    maybeRay = cameraLens.traceUntil(flareRay.ray, reflectionEvent.indexLastReflection + 1,
                                     cameraLens.surfaces.size() - 1, 1, flareRay.lambda, &surfaceNormal);
    if (!maybeRay) {
        return;
    }
    flareRay.ray = *maybeRay;

    const float t = -flareRay.ray.startPoint.z / flareRay.ray.direction.z;
    const Vector3f positionOnSensor = flareRay.ray.constructIntersectionPoint(t);

    if (!filmPhysicalExtend.contains(positionOnSensor.xy())) {
        return;
    };
    const Vector2i pixel = Vector2i(positionOnSensor.x / pixelSize + resolution.getWidth() / 2,
                                    positionOnSensor.y / pixelSize + resolution.getHeight() / 2);

    film.addSample("color", pixel, flareRay.intensity * 0.01f);
};

void FlareRenderer::renderScene() {
    Logger::info("{}", scene.camera->getFocalLength());
    CameraLens &cameraLens = scene.camera->getLens();

    const float aspectRatio = scene.renderSettings.resolution.getRatio();
    float filmbackSize = scene.camera->getFilmbackSize();
    Bounds2df filmPhysicalExtend = Bounds2df({-filmbackSize * 0.1f / 2.f, -filmbackSize * 0.1f / aspectRatio / 2},
                                             {filmbackSize * 0.1f / 2.f, filmbackSize * 0.1f / aspectRatio / 2});
    const float pixelSize = filmPhysicalExtend.getWidth() / scene.renderSettings.resolution.getWidth();

    std::vector<ReflectionEvent> reflectionEvents = createReflectionSequences(cameraLens);

    int samplesPerIteration = 500;
    const size_t samplesPerLight = 1e9;
    const size_t iterations = (samplesPerLight * scene.lights.size()) / samplesPerIteration;
    auto progressController = taskReporter.startTask("Rendering flares", iterations);
    auto rgbBuffer = std::get<Color3fSumBuffer *>(*outputDriver.getFilm().getBufferVariantPtrByName("color"));
    for (auto &light : scene.lights) {
        tbb::parallel_for((size_t)0, samplesPerLight / samplesPerIteration,
                          [&light, &cameraLens, &reflectionEvents, &filmPhysicalExtend, pixelSize, samplesPerLight,
                           &progressController, this, samplesPerIteration, rgbBuffer](size_t sampleIndex) {
                              for (int i = 0; i < samplesPerIteration; i++) {
                                  trace(light, cameraLens.getFirstSurface().apertureRadius, *scene.camera, cameraLens,
                                        reflectionEvents, filmPhysicalExtend, pixelSize, samplesPerLight,
                                        progressController, outputDriver.getFilm(), scene.renderSettings.resolution);
                              }
                              if (progressController.iterationDone() >
                                  TaskReporter::IterationStatus::NO_PROGRESS_INCREMENT) {
                                  outputDriver.updateAllChannels();
                              };
                          });
    }
    outputDriver.updateAllChannels();
    progressController.finish();
}

void FlareRenderer::initialize() {
    outputDriver.initialize(
        FilmSpecBuilder(scene.renderSettings.resolution, FilmBufferType::SUM, PixelFormat::FLOAT32).finish());
    scene.camera->getLens().changeAperture(scene.camera->getFStop());
}

}