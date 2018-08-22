#include <iostream>
#include <Image.h>
#include <Sphere.h>
#include "Camera.h"
#include "PineHoleCameraModel.h"
#include "BmpImageWriter.h"


int main(int argc, char *argv[])
{
    Image myImage(800,600);

    Camera camera(Vector3f(0,0,10), Vector3f(0,1,0), Vector3f(0,0,-1), 6.0f*180.0f/3.141f);
    PineHoleCameraModel cameraModel(camera,myImage.getWidth(),myImage.getHeight());

    Sphere sphere(Vector3f(5,0,-10), 3.0f);

    for(int x=0; x<myImage.getWidth();x++){
        for(int y=0; y<myImage.getHeight();y++){
            Ray ray = cameraModel.createPrimaryRay(x,y);
            if(sphere.intersects(ray)){
                myImage.setValue(x,y,1,1,1);
            }
            //default value is 0,0,0
            //myImage.setValue(x,y,ray.direction.x/2.0f+0.5f, ray.direction.y/2.0f+0.5f, ray.direction.z/2.0f+0.5f);
        }
    }

    BmpImageWriter imageWriter;
    imageWriter.writeImage(myImage, "");

    return 0;
}
