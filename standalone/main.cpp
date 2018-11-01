#include <iostream>
#include <image/Image.h>
#include <scene/Sphere.h>
#include <scene/Scene.h>
#include <image/ImageWriter.h>
#include <image/ImageWriterFactory.h>
#include <utils/ToStringHelper.h>
#include <intersectors/SceneIntersector.h>
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
    PineHoleCameraModel cameraModel(camera,myImage.getWidth(),myImage.getHeight());

    Scene scene;
    SceneIntersector sceneIntersector(scene);

    // todo move to scene creator
    std::cout << "Generating spheres..." << std::endl;
    for(int i=-5; i<5; i+=1){
        Sphere* sphere = new Sphere(Vector3f(i,0,-10), 3.0f);
        scene.addObject(sphere);
    }
    std::cout << "Sphere generation done." << std::endl;

    std::cout << ToStringHelper("Pixel")
            .addMember("x", 6)
            .addMember("y", 7)
            .finish() << std::endl;


    for(int x=0; x<myImage.getWidth();x++){
        for(int y=0; y<myImage.getHeight();y++){
            Ray ray = cameraModel.createPrimaryRay(x,y);

            if(sceneIntersector.intersects(ray)){
                myImage.setValue(x,y,1,1,1);
            }
        }
    }

    std::unique_ptr<ImageWriter> imageWriter(createImageWriter(ImageWriterType::BMP));
    imageWriter->writeImage(myImage, "");

    std::cout << "write" << std::endl;

    SceneWriter sceneWriter(scene);
    sceneWriter.write("test.json");

    std::cout << "read" << std::endl;
    Scene newScene;
    SceneReader sceneReader(newScene);
    sceneReader.read("test.json");

    std::cout << "done" << std::endl;

    std::cout << newScene.objects.size() << std::endl;

    return 0;
}
