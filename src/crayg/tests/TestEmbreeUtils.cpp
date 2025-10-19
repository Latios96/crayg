#include "renderer/intersectors/embree/EmbreeUtils.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("EmbreeUtils::createRtcRay") {

    SECTION("should create RtcRay from given ray") {
        Ray ray({1, 2, 3}, {4, 5, 6});

        RTCRay rtcRay;
        EmbreeUtils::createRtcRay(ray, &rtcRay);

        REQUIRE(rtcRay.org_x == 1);
        REQUIRE(rtcRay.org_y == 2);
        REQUIRE(rtcRay.org_z == 3);
        REQUIRE(rtcRay.dir_x == 4);
        REQUIRE(rtcRay.dir_y == 5);
        REQUIRE(rtcRay.dir_z == 6);
        REQUIRE(rtcRay.tnear == 0.001f);
        REQUIRE(rtcRay.tfar == std::numeric_limits<float>::infinity());
    }

    SECTION("should create RtcRay from given ray with correct tFar") {
        Ray ray({1, 2, 3}, {4, 5, 6});

        RTCRay rtcRay;
        EmbreeUtils::createRtcRay(ray, &rtcRay, 5);

        REQUIRE(rtcRay.tfar == 5);
    }
}

TEST_CASE("EmbreeUtils::createRTCRayHit") {

    SECTION("should create RTCRayHit from given ray") {
        Ray ray({1, 2, 3}, {4, 5, 6});

        RTCRayHit rtcRayHit;
        EmbreeUtils::createRTCRayHit(ray, &rtcRayHit);

        REQUIRE(rtcRayHit.ray.org_x == 1);
        REQUIRE(rtcRayHit.ray.org_y == 2);
        REQUIRE(rtcRayHit.ray.org_z == 3);
        REQUIRE(rtcRayHit.ray.dir_x == 4);
        REQUIRE(rtcRayHit.ray.dir_y == 5);
        REQUIRE(rtcRayHit.ray.dir_z == 6);
        REQUIRE(rtcRayHit.ray.tnear == 0.001f);
        REQUIRE(rtcRayHit.ray.tfar == std::numeric_limits<float>::infinity());
        REQUIRE(rtcRayHit.hit.geomID == RTC_INVALID_GEOMETRY_ID);
    }
    SECTION("should create RTCRayHit from given ray with corrent tFar") {
        Ray ray({1, 2, 3}, {4, 5, 6});

        RTCRayHit rtcRayHit;
        EmbreeUtils::createRTCRayHit(ray, &rtcRayHit, 5);

        REQUIRE(rtcRayHit.ray.tfar == 5);
    }
}

}