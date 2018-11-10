//
// Created by Jan Honsbrok on 04.11.18.
//

#include <image/ImageIterators.h>
#include <intersectors/SceneIntersector.h>
#include <spdlog/spdlog.h>
#include "Renderer.h"
#include "PineHoleCameraModel.h"

Renderer::Renderer(Scene &scene, Image &image) : scene(scene), image(image) {}

void Renderer::renderScene() {

    // create camera model
    PineHoleCameraModel cameraModel(*scene.camera,image.getWidth(),image.getHeight());

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
        auto intersection = sceneIntersector.intersect(ray);
        if(intersection.isValid()){
            image.setValue(pixel.x, pixel.y, shadePoint(intersection.location, *intersection.object));
            //image.setValue(pixel.x, pixel.y, 1,1,1);
        }
    }
    spdlog::get("console")->info("Rendering done.");
}
// todo add tests
Color Renderer::shadePoint(Vector3f point, SceneObject& object) {
    // get normal at point
    Vector3f normal = object.getNormal(point);
    // for every light
    Color color = Color::createGrey(0.2f); // todo take value from rendersettings

    for (const auto& light : scene.lights){
        // calculate light vector
        Vector3f lightVector = (light->getPosition() - point).normalize();

        // skalar produkt zwischen normale und lightVector
        float scalar = normal.scalarProduct(lightVector) * light->getIntensity();

        if (scalar >0){
            color = color+scalar;
        }
    }

    return color;

}
