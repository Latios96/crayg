#include <iostream>
#include <image/Image.h>
#include <Sphere.h>
#include <Scene.h>
#include <prims/Stage.h>
#include <prims/Prim.h>
#include <schemas/SpherePrim.h>
#include <image/ImageWriter.h>
#include <image/ImageWriterFactory.h>
#include "Camera.h"
#include "PineHoleCameraModel.h"


int main(int argc, char *argv[])
{
    Image myImage(800,600);

    Camera camera(Vector3f(0,0,10), Vector3f(0,1,0), Vector3f(0,0,-1), 6.0f*180.0f/3.141f);
    PineHoleCameraModel cameraModel(camera,myImage.getWidth(),myImage.getHeight());

    Scene scene;
    SceneIntersector sceneIntersector(scene);

    std::cout << "Generating spheres..." << std::endl;
    for(int i=-5; i<5; i+=1){
        Sphere* sphere = new Sphere(Vector3f(i,0,-10), 3.0f);
        scene.addObject(sphere);
    }
    std::cout << "Sphere generation done." << std::endl;


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

    return 0;
}
