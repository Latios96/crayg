#define FMT_HEADER_ONLY
#include "fmt/format.h"
#include <iostream>
#include <image/Image.h>
#include <scene/Scene.h>
#include <image/ImageWriter.h>
#include <image/ImageWriterFactory.h>
#include <intersectors/SceneIntersector.h>
#include <Renderer.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <cxxopts.hpp>
#include "sceneIO/SceneReaderFactory.h"

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

    Scene scene;

    // read scene
    std::string scenePath = result["scene"].as<std::string>();
    auto sceneReader = SceneReaderFactory::createSceneWriter(scenePath, scene);
    sceneReader->read();

    Renderer renderer(scene, myImage);
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
