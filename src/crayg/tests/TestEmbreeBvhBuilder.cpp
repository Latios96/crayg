#include <catch2/catch.hpp>
#include "fixtures/TriangleMeshFixtures.h"
#include "intersectors/embree/EmbreeBvhBuilder.h"

namespace crayg {

TEST_CASE("EmbreeBvhBuilder::build") {

    SECTION("building for empty scene should work") {
        Scene scene;

        EmbreeBvhBuilder embreeBvhBuilder(scene);
        auto embreeBvh = embreeBvhBuilder.build();

        REQUIRE(embreeBvh != nullptr);
    }

    SECTION("should support all supported geometry types") {
        Scene scene;
        scene.addObject(std::shared_ptr<TriangleMesh>(TriangleMeshFixtures::createPrimVarFixtureMesh()));
        auto sphere = std::make_shared<Sphere>(Vector3f(0.f, 1.f, 0.f), 1.f);
        scene.addObject(sphere);

        EmbreeBvhBuilder embreeBvhBuilder(scene);
        auto embreeBvh = embreeBvhBuilder.build();

        REQUIRE(embreeBvh->geomIdToSceneObject.size() == 2);
        REQUIRE(embreeBvh->geomIdToSceneObject[0] == EmbreeMappingEntry(0u, EmbreePrimitiveType::TRIANGLE_MESH));
        REQUIRE(embreeBvh->geomIdToSceneObject[1] == EmbreeMappingEntry(1u, EmbreePrimitiveType::SPHERE));
    }
}

}