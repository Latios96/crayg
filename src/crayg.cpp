#include<iostream>
#include <cstring>
#include "Image.h"
#include "BmpImageWriter.h"
#include "Camera.h"
#include "PineHoleCameraModel.h"

// todo use proper Color class


int main(int argc, char* argv[]) {
	// global setup...

	/*int result = Catch::Session().run(argc, argv);

	// global clean-up...
	return result;*/
    Image myImage(600,400);

    /*for (int i=0; i<100;i++){
        myImage.set_value(i,10, 1,1,1);
    }*/
    //myImage.set_value(10,10,1,1,1);

    Camera camera(Vector3f(0,0,0), Vector3f(0,1,0), Vector3f(0,0,-1), 120.0f);
    PineHoleCameraModel cameraModel(camera,myImage.get_width(),myImage.get_height());

    for(int x=0; x<myImage.get_width();x++){
        for(int y=0; y<myImage.get_height();y++){
            Ray ray = cameraModel.createPrimaryRay(x,y);
            myImage.set_value(x,y,ray.direction.x/2.0f+0.5f, ray.direction.y/2.0f+0.5f, ray.direction.z/2.0f+0.5f);
        }
    }



    BmpImageWriter imageWriter;
    imageWriter.write_image(myImage, "");

	return 0;
}