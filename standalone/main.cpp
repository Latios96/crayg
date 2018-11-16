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
#include <scene/TriangeMesh.h>
#include <sceneIO/JsonDeserializer.h>

const std::string VERSION = "0.2.0";

int main(int argc, char *argv[])
{
    /*std::string line("v 1.6831 3.0852 -0.9792");
    std::istringstream v(std::stof(line));
    double x,y,z;
    v>>x;v>>y;v>>z;
    std::cout << ToStringHelper("Vector3f").addMember("x", x).addMember("y",y).addMember("z", z).finish() << std::endl;*/

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
    SceneReader sceneReader(scene);
    sceneReader.read(scenePath);

    /*scene.camera = new Camera({3, 5, -8}, {0,1,0}, {0,0,0});
    scene.camera->setFocalLength(35);
    scene.camera->setFilmbackSize(36);

    TriangleMesh *cube = new TriangleMesh();
    TriangleMesh::createCube(*cube);
    scene.addObject(cube);

    auto sphere = new Sphere({-5,0,0}, 1);
    scene.addObject(sphere);
    auto sphere2 = new Sphere({-5,0,2}, 1.5);
    scene.addObject(sphere2);


    Light *light = new Light();
    light->setPosition({0,5,1});
    light->setIntensity(1);
    scene.addLight(light);*/

    SceneIntersector sceneIntersector(scene);

    // render the scene
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
