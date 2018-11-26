//
// Created by Jan Honsbrok on 04.11.18.
//

#include <image/ImageIterators.h>
#include <spdlog/spdlog.h>
#include "Renderer.h"
#include "PineHoleCameraModel.h"
#include "utils/ProgressReporter.h"

Renderer::Renderer(Scene &scene, Image &image) : scene(scene), image(image) {}

// todo init should not be in renderScene
void Renderer::renderScene() {
    init();

    spdlog::get("console")->info("Starting rendering..");

    int pixelCount = image.getHeight() * image.getWidth();
    ProgressReporter reporter = ProgressReporter::createLoggingProgressReporter(pixelCount, "Rendering done by {}%");

    for(auto pixel : ImageIterators::lineByLine(image)){
        //if (pixel.x == 371 && pixel.y == 259){
            renderPixel(pixel);
            reporter.iterationDone();
        //}
    }
    spdlog::get("console")->info("Rendering done.");
}

void Renderer::init(){
    cameraModel = std::shared_ptr<CameraModel>(new PineHoleCameraModel(*scene.camera, image.getWidth(), image.getHeight()));
    lambertMethod = std::shared_ptr<ShadingMethod>(new ShadingMethod(scene));

    spdlog::get("console")->info("Execute Imageable::beforeRender...");
    for(auto &imageable : scene.objects){
        imageable->beforeRender();
    }

    spdlog::get("console")->info("Creating SceneIntersector...");
    sceneIntersector = std::shared_ptr<SceneIntersector>(new SceneIntersector(scene));
}

void Renderer::renderPixel(const PixelPosition &pixel) {
    Ray ray = cameraModel->createPrimaryRay(pixel.x, pixel.y);

    auto intersection = sceneIntersector->intersect(ray);
    if(intersection.imageable){
        Vector3f location = ray.startPoint + (ray.direction * intersection.rayParameter);
        Imageable &object = *intersection.imageable;
        Color shadedColor = lambertMethod->lambertShading(location, object);
        image.setValue(pixel.x, pixel.y, shadedColor);
    }
}

