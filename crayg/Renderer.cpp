//
// Created by Jan Honsbrok on 04.11.18.
//

#include <image/ImageIterators.h>
#include <intersectors/SceneIntersector.h>
#include <spdlog/spdlog.h>
#include "Renderer.h"
#include "PineHoleCameraModel.h"

Renderer::Renderer(Scene &scene, Camera &camera, Image &image) : scene(scene), camera(camera), image(image) {}

void Renderer::renderScene() {

    // create camera model
    PineHoleCameraModel cameraModel(camera,image.getWidth(),image.getHeight());

    spdlog::get("console")->info("Creating SceneIntersector...");
    // create scene intersector
    SceneIntersector sceneIntersector(scene);

    // for every pixel
    // todo report progress
    spdlog::get("console")->info("Starting rendering..");
    for(auto pixel : ImageIterators::lineByLine(image)){
        // create ray
        Ray ray = cameraModel.createPrimaryRay(pixel.x,pixel.y);

        // if intersects, set white color
        if(sceneIntersector.intersects(ray)){
            image.setValue(pixel.x,pixel.y,1,1,1);
        }
    }
    spdlog::get("console")->info("Rendering done.");
}
