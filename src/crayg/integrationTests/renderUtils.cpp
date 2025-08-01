#include "renderUtils.h"
#include "image/film/io/FilmWriter.h"
#include "utils/TaskReporter.h"

namespace crayg {

void renderScene(const std::string &scenePath, const std::string imageOutputPath, const Resolution resolution) {
    NextGenOutputDriver outputDriver;

    Scene scene;
    scene.renderSettings.resolution = resolution;
    scene.renderSettings.maxSamples = 4;

    auto sceneReader = SceneReaderFactory::createSceneReader(scenePath, scene);
    sceneReader->read();

    TaskReporter taskReporter;
    BucketQueue bucketQueue([]() { return Vector2i(); });
    Renderer renderer(scene, outputDriver, taskReporter, bucketQueue);
    renderer.initOutputDriver();
    renderer.renderScene();

    FilmWriter::writeFilm(outputDriver.getFilm(), imageOutputPath);
}

}