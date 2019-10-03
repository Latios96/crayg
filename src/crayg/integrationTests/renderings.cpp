//
// Created by jan on 03/10/2019.
//#include <image/Image.h>
#include <scene/Scene.h>
#include <Renderer.h>
#include <image/ImageWriter.h>
#include <sceneIO/SceneReaderFactory.h>
#include <image/ImageWriterFactory.h>
#include "KnipserAssertions.h"
#include "KnipserApp.h"
void renderScene(const std::string &scenePath, const std::string imageOutputPath) {
    Image myImage(800, 600);

    Scene scene;

    auto sceneReader = SceneReaderFactory::createSceneWriter(scenePath, scene);
    sceneReader->read();

    Renderer renderer(scene, myImage);
    renderer.renderScene();

    std::unique_ptr<ImageWriter> imageWriter(createImageWriter(ImageWriterType::BMP));

    imageWriter->writeImage(myImage, imageOutputPath);
}

KNIPSER_REGISTER_TEST(singleSphere, [](TestContext &context) {
    context.setImageOutputName("singleSphere.bmp");
    renderScene(context.getReferenceFolder() + "/singleSphere.json", context.getOutputFilename());

    ImagesAreEqualAssertion<OpenImageIoImageComparator> imagesAreEqualAssertion(__FILE__, __LINE__);
    imagesAreEqualAssertion.doAssert(context);
})

KNIPSER_REGISTER_TEST(threeSpheres, [](TestContext &context) {
    context.setImageOutputName("threeSpheres.bmp");
    renderScene(context.getReferenceFolder() + "/threeSpheres.json", context.getOutputFilename());

    ImagesAreEqualAssertion<OpenImageIoImageComparator> imagesAreEqualAssertion(__FILE__, __LINE__);
    imagesAreEqualAssertion.doAssert(context);
})