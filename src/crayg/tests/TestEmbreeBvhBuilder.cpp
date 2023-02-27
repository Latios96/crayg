#include "fixtures/SubdivisionSurfaceMeshFixtures.h"
#include "fixtures/TriangleMeshFixtures.h"
#include "intersectors/embree/EmbreeBvhBuilder.h"
#include "scene/primitives/Sphere.h"
#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include <catch2/catch.hpp>

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
        auto triangleMesh = std::shared_ptr<TriangleMesh>(TriangleMeshFixtures::createPrimVarFixtureMesh());
        scene.addObject(triangleMesh);
        auto sphere = std::make_shared<Sphere>(Vector3f(0.f, 1.f, 0.f), 1.f);
        scene.addObject(sphere);
        auto subdivisionSurfaceMesh = std::make_shared<SubdivisionSurfaceMesh>();
        SubdivisionSurfaceMeshFixtures::createUnitPlane(*subdivisionSurfaceMesh);
        scene.addObject(subdivisionSurfaceMesh);

        EmbreeBvhBuilder embreeBvhBuilder(scene);
        auto embreeBvh = embreeBvhBuilder.build();

        REQUIRE(embreeBvh->geomIdToSceneObject.size() == 3);
        REQUIRE(embreeBvh->geomIdToSceneObject[0] == EmbreeMappingEntry(0u, EmbreePrimitiveType::TRIANGLE_MESH));
        REQUIRE(embreeBvh->geomIdToSceneObject[1] == EmbreeMappingEntry(1u, EmbreePrimitiveType::SPHERE));
        REQUIRE(embreeBvh->geomIdToSceneObject[2] ==
                EmbreeMappingEntry(2u, EmbreePrimitiveType::SUBDIVISION_SURFACE_MESH));
    }
}

}