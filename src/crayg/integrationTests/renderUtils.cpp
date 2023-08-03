#include "renderUtils.h"
#include "utils/TaskReporter.h"

namespace crayg {

void renderScene(const std::string &scenePath, const std::string imageOutputPath, const Resolution resolution) {
    Image myImage(resolution);
    ImageOutputDriver imageOutputDriver(myImage);

    Scene scene;
    scene.renderSettings.resolution = resolution;
    scene.renderSettings.maxSamples = 4;

    auto sceneReader = SceneReaderFactory::createSceneReader(scenePath, scene);
    sceneReader->read();

    TaskReporter taskReporter;
    BucketQueue bucketQueue([]() { return Vector2i(); });
    Renderer renderer(scene, imageOutputDriver, taskReporter, bucketQueue);
    renderer.renderScene();

    ImageWriters::writeImage(myImage, imageOutputPath);
}

}