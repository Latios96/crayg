#include <Sphere.h>
#include <catch.hpp>

TEST_CASE("Sphere") {
    Sphere mySphere(Vector3f(0, 0, 0), 3.0f);

    SECTION("createSphere") {
        // make sure radius is correctly set
        REQUIRE(mySphere.getRadius() == 3.0f);
    }

    SECTION("intersects") {
        // test intersecting ray
        Ray intersectingRay(Vector3f(1, 0, 0), Vector3f(-1, 0, 0));
        // intersects should return true
        REQUIRE(mySphere.intersects(intersectingRay));

        // test not intersecting ray
        Ray notIntersectingRay(Vector3f(0, 0, 5), Vector3f(-1, 0, 0));
        // intersects should return true
        REQUIRE_FALSE(mySphere.intersects(notIntersectingRay));
    }
    // todo test serialize
}

TEST_CASE( "Sphere/transformation") {
    Sphere mySphere(Vector3f(1,2,3),3.0f);
    
    REQUIRE(mySphere.getPosition() == Vector3f(1,2,3));
}
TEST_CASE( "Sphere/intersectsTransformed") {
    Sphere mySphere(Vector3f(1,2,3),1.0f);

    REQUIRE(mySphere.intersects(Ray(Vector3f(1,2,6), Vector3f(0,0,-1))));
}


