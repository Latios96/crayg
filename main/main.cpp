#include <iostream>
#include <Image.h>
#include "Camera.h"
#include "PineHoleCameraModel.h"
#include "BmpImageWriter.h"


int main(int argc, char *argv[])
{
    Image myImage(600,400);

    Camera camera(Vector3f(0,0,0), Vector3f(0,1,0), Vector3f(0,0,-1), 120.0f);
    PineHoleCameraModel cameraModel(camera,myImage.getWidth(),myImage.getHeight());

    for(int x=0; x<myImage.getWidth();x++){
        for(int y=0; y<myImage.getHeight();y++){
            Ray ray = cameraModel.createPrimaryRay(x,y);
            myImage.setValue(x,y,ray.direction.x/2.0f+0.5f, ray.direction.y/2.0f+0.5f, ray.direction.z/2.0f+0.5f);
        }
    }

    BmpImageWriter imageWriter;
    imageWriter.write_image(myImage, "");

    return 0;
}
