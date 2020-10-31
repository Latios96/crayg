//
// Created by jan on 03/10/2019.
#include <scene/Scene.h>
#include <Renderer.h>
#include <image/ImageWriter.h>
#include <sceneIO/SceneReaderFactory.h>
#include <image/ImageWriters.h>
#include "KnipserAssertions.h"
#include "KnipserApp.h"

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

std::vector<KnipserTest> renderTests() {
    return {
        KnipserTest("singleSphere", [](TestContext &context) {
            context.setImageOutputName("singleSphere.png");
            renderScene(context.getReferenceFolder() + "/singleSphere.json", context.getOutputFilename());

            ASSERT_IMAGES_ARE_EQUAL(context);
        }),
        KnipserTest("threeSpheres", [](TestContext &context) {
            context.setImageOutputName("threeSpheres.png");
            renderScene(context.getReferenceFolder() + "/threeSpheres.json", context.getOutputFilename());

            ASSERT_IMAGES_ARE_EQUAL(context);
        }),
        KnipserTest("pointCloud", [](TestContext &context) {
            context.setImageOutputName("pointCloud.png");
            renderScene(context.getReferenceFolder() + "/pointCloud.json", context.getOutputFilename());

            ASSERT_IMAGES_ARE_EQUAL(context);
        })

    };
}