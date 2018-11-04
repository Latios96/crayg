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

const std::string VERSION = "0.1.0";

int main(int argc, char *argv[])
{
    std::cout << fmt::format("Crayg Renderer version {}\n", VERSION);
    Image myImage(800,600);

    Camera camera(Vector3f(0,0,10), Vector3f(0,1,0), Vector3f(0,0,-1), 6.0f*180.0f/3.141f);

    Scene scene;
    SceneIntersector sceneIntersector(scene);

    // todo move to scene creator
    std::cout << "Generating spheres..." << std::endl;
    for(int i=-5; i<5; i+=1){
        Sphere* sphere = new Sphere(Vector3f(i,0,-10), 3.0f);
        scene.addObject(sphere);
    }
    std::cout << "Sphere generation done." << std::endl;

    Renderer renderer(scene, camera, myImage);
    renderer.renderScene();

    std::unique_ptr<ImageWriter> imageWriter(createImageWriter(ImageWriterType::BMP));
    imageWriter->writeImage(myImage, "img.bmp");

    return 0;
}
