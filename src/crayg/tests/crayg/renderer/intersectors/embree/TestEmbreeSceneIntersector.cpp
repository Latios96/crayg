#include "crayg/renderer/intersectors/embree/EmbreeBvhBuilder.h"
#include "crayg/renderer/intersectors/embree/EmbreeSceneIntersector.h"
#include "crayg/scene/primitives/Sphere.h"
#include "crayg/scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include "fixtures/PointInstancerFixtures.h"
#include "fixtures/SubdivisionSurfaceMeshFixtures.h"
#include "fixtures/TriangleMeshFixtures.h"
#include <catch2/catch.hpp>

namespace crayg {

const Ray RAY_WITH_NO_INTERSECTION = Ray({0, 5, 0}, {1, 0, 0});
const Ray RAY_WITH_TRIANGLE_INTERSECTION = Ray({0.75f, -1, 1.5f}, {0, 1, 0});
const Ray RAY_WITH_SUBD_MESH_INTERSECTION = Ray({0.1f, -1, 0}, {0, 1, 0});
const Ray RAY_WITH_SPHERE_INTERSECTION = Ray({-2, 2, 0}, {1, 0, 0});
const Ray RAY_ON_TRIANGLE = Ray({0.75f, 0, 1.5f}, {0, 1, 0});

struct IntersectorFixture {
    explicit IntersectorFixture(Scene &scene) : scene(scene) {
        EmbreeBvhBuilder embreeBvhBuilder(scene);
        auto embreeBvh = embreeBvhBuilder.build();
        embreeSceneIntersector = std::make_unique<EmbreeSceneIntersector>(scene, std::move(embreeBvh));
    }

    Scene &scene;
    std::unique_ptr<EmbreeSceneIntersector> embreeSceneIntersector;
};

TEST_CASE("EmbreeSceneIntersector::intersect") {
    Scene scene;
    scene.addObject(std::shared_ptr<TriangleMesh>(TriangleMeshFixtures::createPrimVarFixtureMesh()));
    auto sphere = std::make_shared<Sphere>(Vector3f(0.f, 2.f, 0.f), 1.f);
    scene.addObject(sphere);
    HitStorage hitStorage;

    SECTION("should find no intersection for empty scene") {
        Scene emptyScene;
        IntersectorFixture fixture(emptyScene);

        auto intersection = fixture.embreeSceneIntersector->intersect(RAY_WITH_NO_INTERSECTION, hitStorage);

        REQUIRE_FALSE(intersection.isValid());
    }

    SECTION("should find no intersection for scene with TriangleMesh and Sphere") {
        IntersectorFixture fixture(scene);

        auto intersection = fixture.embreeSceneIntersector->intersect(RAY_WITH_NO_INTERSECTION, hitStorage);

        REQUIRE_FALSE(intersection.isValid());
    }

    SECTION("should find intersection for Triangle") {
        IntersectorFixture fixture(scene);

        auto intersection = fixture.embreeSceneIntersector->intersect(RAY_WITH_TRIANGLE_INTERSECTION, hitStorage);

        REQUIRE(intersection.isValid());
        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(1.0f));
        auto triangle = dynamic_cast<Triangle *>(intersection.imageable);
        REQUIRE(triangle->faceId == 3);
    }

    SECTION("should find intersection for SubdivisionSurfaceMesh") {
        Scene scene;
        auto subdivisionSurfaceMesh = std::make_shared<SubdivisionSurfaceMesh>();
        SubdivisionSurfaceMeshFixtures::createUnitPlane(*subdivisionSurfaceMesh);
        subdivisionSurfaceMesh->tessellate();
        scene.addObject(subdivisionSurfaceMesh);
        IntersectorFixture fixture(scene);

        auto intersection = fixture.embreeSceneIntersector->intersect(RAY_WITH_SUBD_MESH_INTERSECTION, hitStorage);

        REQUIRE(intersection.isValid());
        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(1.0f));
        auto triangle = dynamic_cast<Triangle *>(intersection.imageable);
        REQUIRE(triangle->faceId == 64);
    }

    SECTION("should find intersection for Sphere") {
        IntersectorFixture fixture(scene);

        auto intersection = fixture.embreeSceneIntersector->intersect(RAY_WITH_SPHERE_INTERSECTION, hitStorage);

        REQUIRE(intersection.isValid());
        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(1.0f));
        auto sphere = dynamic_cast<Sphere *>(intersection.imageable);
        REQUIRE(sphere->getRadius() == 1.f);
    }

    SECTION("should ignore triangle if ray starts at triangle") {
        IntersectorFixture fixture(scene);

        auto intersection = fixture.embreeSceneIntersector->intersect(RAY_ON_TRIANGLE, hitStorage);

        REQUIRE_FALSE(intersection.isValid());
    }

    SECTION("should find intersection for instanced TriangleMesh") {
        Scene scene;
        auto pointInstancer = std::make_shared<PointInstancer>();
        PointInstancerFixtures::createInstancerWithSingleTriangleProtoType(*pointInstancer);
        scene.addObject(pointInstancer);
        IntersectorFixture fixture(scene);

        auto intersection = fixture.embreeSceneIntersector->intersect(RAY_WITH_TRIANGLE_INTERSECTION, hitStorage);

        REQUIRE(intersection.isValid());
        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(1.0f));
        auto triangle = dynamic_cast<Triangle *>(intersection.imageable);
        REQUIRE(triangle->faceId == 3);
    }

    SECTION("should find intersection for instanced SubdivisionSurfaceMesh") {
        Scene scene;
        auto pointInstancer = std::make_shared<PointInstancer>();
        PointInstancerFixtures::createInstancerWithSingleSubdivisionSurfaceMeshProtoType(*pointInstancer);
        std::dynamic_pointer_cast<SubdivisionSurfaceMesh>(pointInstancer->protos[0]->members[0])->tessellate();
        scene.addObject(pointInstancer);
        IntersectorFixture fixture(scene);

        auto intersection = fixture.embreeSceneIntersector->intersect(RAY_WITH_SUBD_MESH_INTERSECTION, hitStorage);

        REQUIRE(intersection.isValid());
        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(1.0f));
        auto triangle = dynamic_cast<Triangle *>(intersection.imageable);
        REQUIRE(triangle->faceId == 64);
    }

    SECTION("should find intersection for instanced Sphere") {
        Scene scene;
        auto pointInstancer = std::make_shared<PointInstancer>();
        PointInstancerFixtures::createInstancerWithSingleSphereProtoType(*pointInstancer);
        auto sphere = std::dynamic_pointer_cast<Sphere>(pointInstancer->protos[0]->members[0]);
        sphere->setTransform(Transform::withPosition({0.f, 2.f, 0.f}));
        sphere->setRadius(1);

        scene.addObject(pointInstancer);
        IntersectorFixture fixture(scene);

        auto intersection = fixture.embreeSceneIntersector->intersect(RAY_WITH_SPHERE_INTERSECTION, hitStorage);

        REQUIRE(intersection.isValid());
        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(1.0f));
        auto sphereI = dynamic_cast<Sphere *>(intersection.imageable);
        REQUIRE(sphereI->getRadius() == 1.f);
    }
}

TEST_CASE("EmbreeSceneIntersector::isOccluded") {
    Scene scene;
    auto sphere1 = std::make_shared<Sphere>(Vector3f(0.f, 0.f, 2.f), 1.f);
    scene.addObject(sphere1);
    HitStorage hitStorage;

    SECTION("should find intersection for empty scene") {
        Scene emptyScene;
        IntersectorFixture fixture(emptyScene);
        Ray ray({0, 0, 0}, {0, 0, 1});

        REQUIRE_FALSE(fixture.embreeSceneIntersector->isOccluded(ray, hitStorage, 1.5f));
    }

    SECTION("should find no intersection for empty scene") {
        Scene emptyScene;
        IntersectorFixture fixture(emptyScene);
        Ray ray({0, 0, 0}, {0, 0, 1});

        REQUIRE_FALSE(fixture.embreeSceneIntersector->isOccluded(ray, hitStorage, 0.5f));
    }
}

}