#include <Sphere.h>
#include "gtest/gtest.h"



TEST(SphereTest, createSphere) {
    Sphere mySphere(Vector3f(0,0,0),3.0f);

    // make sure radius is correctly set
    EXPECT_EQ(mySphere.getRadius(), 3.0f);
}

TEST(SphereTest, intersects) {
    Sphere mySphere(Vector3f(0,0,0),3.0f);

    // test intersecting ray
    Ray intersectingRay(Vector3f(1,0,0), Vector3f(-1,0,0));
    // intersects should return true
    ASSERT_TRUE(mySphere.intersects(intersectingRay));

    // test not intersecting ray
    Ray notIntersectingRay(Vector3f(0,0,5), Vector3f(-1,0,0));
    // intersects should return true
    ASSERT_FALSE(mySphere.intersects(notIntersectingRay));
}
// todo intersection test with transformation
TEST(SphereTest, transformation){
    Sphere mySphere(Vector3f(1,2,3),3.0f);
    
    EXPECT_EQ(mySphere.getPosition(), Vector3f(1,2,3));
}