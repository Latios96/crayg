#include <image/Image.h>
#include <catch.hpp>


TEST_CASE( "Image/constructImage", "[Image]" ) {
    Image myImage(200,100);

    // make sure size is correct
    REQUIRE(myImage.getWidth() == 200);
    REQUIRE(myImage.getHeight() == 100);

    // check image is 0 initialized

    for(int x=0;x<myImage.getWidth();x++){
        for(int y=0;y<myImage.getHeight();y++){
            Vector3f color = myImage.getValue(x,y);
            REQUIRE(color.x == 0);
            REQUIRE(color.y == 0);
            REQUIRE(color.z == 0);
        }
    }
}
TEST_CASE( "Image/copyImage", "[Image]" ) {
    Image myImage(200,100);

    for(int x=0;x<myImage.getWidth();x++){
        for(int y=0;y<myImage.getHeight();y++){
            myImage.setValue(x,y, x*y,x*y,x*y);
        }
    }

    Image otherImage(myImage);
    
    REQUIRE(myImage.getHeight() == otherImage.getHeight());
    REQUIRE(myImage.getWidth() == otherImage.getWidth());

    for(int x=0;x<otherImage.getWidth();x++){
        for(int y=0;y<otherImage.getHeight();y++){
            Vector3f color = otherImage.getValue(x,y);
            REQUIRE(color.x == x*y);
            REQUIRE(color.y == x*y);
            REQUIRE(color.z == x*y);
        }
    }
}
