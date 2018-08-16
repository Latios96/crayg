#include<iostream>
#include <cstring>
#include "Image.h"
#include "BmpImageWriter.h"

// todo use proper Color class


int main(int argc, char* argv[]) {
	// global setup...

	/*int result = Catch::Session().run(argc, argv);

	// global clean-up...
	return result;*/
    Image myImage(100,100);

    /*for (int i=0; i<100;i++){
        myImage.set_value(i,10, 1,1,1);
    }*/
    myImage.set_value(10,10,1,1,1);

    BmpImageWriter imageWriter;
    imageWriter.write_image(myImage, "");

	return 0;
}