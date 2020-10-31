//
// Created by Jan on 31.10.2020.
//
#include "renderUtils.h"

void renderScene(const std::string &scenePath, const std::string imageOutputPath) {
    const Resolution resolution = Resolution(800, 600);
    Image myImage(resolution);
    ImageOutputDriver imageOutputDriver(myImage);

    Scene scene;
    scene.renderSettings.resolution = resolution;
    scene.renderSettings.maxSamples = 4;

    auto sceneReader = SceneReaderFactory::createSceneWriter(scenePath, scene);
    sceneReader->read();

    Renderer renderer(scene, imageOutputDriver);
    renderer.renderScene();

    ImageWriters::writeImage(myImage, imageOutputPath);
}