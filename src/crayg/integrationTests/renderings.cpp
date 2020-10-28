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
    Image myImage(800, 600);

    Scene scene;

    auto sceneReader = SceneReaderFactory::createSceneWriter(scenePath, scene);
    sceneReader->read();

    Renderer renderer(scene, myImage);
    renderer.renderScene();

    ImageWriters::writeImage(myImage, imageOutputPath);
}

KNIPSER_REGISTER_TEST(singleSphere, [](TestContext &context) {
    context.setImageOutputName("singleSphere.png");
    renderScene(context.getReferenceFolder() + "/singleSphere.json", context.getOutputFilename());

    ASSERT_IMAGES_ARE_EQUAL(context);
})

KNIPSER_REGISTER_TEST(threeSpheres, [](TestContext &context) {
    context.setImageOutputName("threeSpheres.png");
    renderScene(context.getReferenceFolder() + "/threeSpheres.json", context.getOutputFilename());

    ASSERT_IMAGES_ARE_EQUAL(context);
})

KNIPSER_REGISTER_TEST(pointCloud, [](TestContext &context) {
    context.setImageOutputName("pointCloud.png");
    renderScene(context.getReferenceFolder() + "/pointCloud.json", context.getOutputFilename());

    ASSERT_IMAGES_ARE_EQUAL(context);
})