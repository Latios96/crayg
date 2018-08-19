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
