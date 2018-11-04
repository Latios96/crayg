#include <iostream>
#include <image/Image.h>
#include <scene/Sphere.h>
#include <scene/Scene.h>
#include <image/ImageWriter.h>
#include <image/ImageWriterFactory.h>
#include <utils/ToStringHelper.h>
#include <intersectors/SceneIntersector.h>
#include <Renderer.h>
#include "scene/Camera.h"
#include "PineHoleCameraModel.h"
#include "image/ImageIterators.h"
#include "sceneIO/SceneWriter.h"
#include "sceneIO/SceneReader.h"
#define FMT_HEADER_ONLY
#include "fmt/format.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

const std::string VERSION = "0.1.0";

int main(int argc, char *argv[])
{
    auto console = spdlog::stdout_color_mt("console");

    console->info("Crayg Renderer version {}", VERSION);

    Image myImage(800,600);

    Camera camera(Vector3f(0,0,10), Vector3f(0,1,0), Vector3f(0,0,-1), 6.0f*180.0f/3.141f);

    Scene scene;
    SceneIntersector sceneIntersector(scene);

    // todo move to scene creator
    console->info("Generating spheres...");

    for(int i=-5; i<5; i+=1){
        Sphere* sphere = new Sphere(Vector3f(i,0,-10), 3.0f);
        scene.addObject(sphere);
    }
    console->info("Sphere generation done.");

    Renderer renderer(scene, camera, myImage);
    renderer.renderScene();

    console->info("writing image..");
    std::unique_ptr<ImageWriter> imageWriter(createImageWriter(ImageWriterType::BMP));
    imageWriter->writeImage(myImage, "img.bmp");
    console->info("writing image done.");

    return 0;
}
