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
#include <cxxopts.hpp>

const std::string VERSION = "0.2.0";

int main(int argc, char *argv[])
{
    cxxopts::Options options("Crayg Renderer", "CLI Interface for Crayg renderer");

    options.add_options()
            ("s,scene", "Scene to render", cxxopts::value<std::string>())
            ("o,output", "path to the rendered image", cxxopts::value<std::string>())
            ;

    auto result = options.parse(argc, argv);

    auto console = spdlog::stdout_color_mt("console");

    console->info("Crayg Renderer version {}", VERSION);

    Image myImage(800,600);

    Camera camera(Vector3f(0,0,10), Vector3f(0,1,0), Vector3f(0,0,-1), 6.0f*180.0f/3.141f);
    /*Camera camera(Vector3f(2.437052995026952f,
                           2.642462443303262f,
                           7.590531325024573f),
                    Vector3f(0,1,0),
                    Vector3f(4.1744385725905886e-14f,
                             4.884981308350689e-15f,
                             4.529709940470639e-14f).normalize(),
                    6.0f*180.0f/3.141f);*/

    Scene scene;
    SceneIntersector sceneIntersector(scene);

    // read scene
    std::string scenePath = result["scene"].as<std::string>();
    SceneReader sceneReader(scene);
    sceneReader.read(scenePath);

    // render the scene
    Renderer renderer(scene, camera, myImage);
    renderer.renderScene();

    console->info("writing image..");
    std::unique_ptr<ImageWriter> imageWriter(createImageWriter(ImageWriterType::BMP));

    if (result["output"].count()){
        imageWriter->writeImage(myImage, result["output"].as<std::string>());
    }
    else{
        imageWriter->writeImage(myImage, "img.bmp");
    }
    console->info("writing image done.");

    return 0;
}
