//
// Created by Jan Honsbrok on 01.10.19.
//
#include <image/Image.h>
#include <scene/Scene.h>
#include <Renderer.h>
#include <image/ImageWriter.h>
#include <sceneIO/SceneReaderFactory.h>
#include <image/ImageWriterFactory.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "KnipserApp.h"
#include "KnipserAssertions.h"

void renderScene(const std::string& scenePath, const std::string imageOutputPath){
    Image myImage(800, 600);

    Scene scene;

    auto sceneReader = SceneReaderFactory::createSceneWriter(scenePath, scene);
    sceneReader->read();

    Renderer renderer(scene, myImage);
    renderer.renderScene();

    std::unique_ptr<ImageWriter> imageWriter(createImageWriter(ImageWriterType::BMP));

    imageWriter->writeImage(myImage, imageOutputPath);
}

KNIPSER_REGISTER_TEST(singleSphere, [](const TestContext &context){
    renderScene(context.getReferenceFolder() + "/singleSphere.json", context.getOutputFilename());
    ImagesAreEqualAssertion<OpenImageIoImageComparator> imagesAreEqualAssertion (__FILE__, __LINE__);
    imagesAreEqualAssertion.doAssert(context);
});
bool testRegistrationResult_threeSpheres = TestRegistry::getInstance()->registerTest(KnipserTest(std::string("threeSpheres"), [](const TestContext &context){
    renderScene(context.getReferenceFolder() + "/threeSpheres.json", context.getOutputFilename());
    ImagesAreEqualAssertion<OpenImageIoImageComparator> imagesAreEqualAssertion (__FILE__, __LINE__);
    imagesAreEqualAssertion.doAssert(context);
}));

int main(int argc, char **argv) {
    auto console = spdlog::stdout_color_mt("console");
    KNIPSER_MAIN;
}