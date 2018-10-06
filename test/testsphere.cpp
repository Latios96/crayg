#include <Sphere.h>
#include <catch.hpp>


TEST_CASE( "createSphere", "[Sphere]" ) {
    Sphere mySphere(Vector3f(0,0,0),3.0f);

    // make sure radius is correctly set
    REQUIRE(mySphere.getRadius() == 3.0f);
}

TEST_CASE( "intersects", "[Sphere]" ) {
    Sphere mySphere(Vector3f(0,0,0),3.0f);

    // test intersecting ray
    Ray intersectingRay(Vector3f(1,0,0), Vector3f(-1,0,0));
    // intersects should return true
    REQUIRE(mySphere.intersects(intersectingRay));

    // test not intersecting ray
    Ray notIntersectingRay(Vector3f(0,0,5), Vector3f(-1,0,0));
    // intersects should return true
    REQUIRE_FALSE(mySphere.intersects(notIntersectingRay));
}
// todo intersection test with transformation
TEST_CASE( "transformation", "[Sphere]" ) {
    Sphere mySphere(Vector3f(1,2,3),3.0f);
    
    REQUIRE(mySphere.getPosition() == Vector3f(1,2,3));
}