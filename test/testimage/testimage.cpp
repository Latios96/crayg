#include <Image.h>
#include "gtest/gtest.h"


TEST(ImageTest, constructImage) {
    Image myImage(200,100);

    // make sure size is correct
    EXPECT_EQ(myImage.getWidth(),200);
    EXPECT_EQ(myImage.getHeight(), 100);

    // check image is 0 initialized

    for(int x=0;x<myImage.getWidth();x++){
        for(int y=0;y<myImage.getHeight();y++){
            Vector3f color = myImage.getValue(x,y);
            EXPECT_EQ(color.x, 0);
            EXPECT_EQ(color.y, 0);
            EXPECT_EQ(color.z, 0);
        }
    }
}
TEST(ImageTest_constructImage_Test, copyImage){
    Image myImage(200,100);

    for(int x=0;x<myImage.getWidth();x++){
        for(int y=0;y<myImage.getHeight();y++){
            myImage.setValue(x,y, x*y,x*y,x*y);
        }
    }

    Image otherImage(myImage);
    
    EXPECT_EQ(myImage.getHeight(), otherImage.getHeight());
    EXPECT_EQ(myImage.getWidth(), otherImage.getWidth());

    for(int x=0;x<otherImage.getWidth();x++){
        for(int y=0;y<otherImage.getHeight();y++){
            Vector3f color = otherImage.getValue(x,y);
            EXPECT_EQ(color.x, x*y);
            EXPECT_EQ(color.y, x*y);
            EXPECT_EQ(color.z, x*y);
        }
    }
}
