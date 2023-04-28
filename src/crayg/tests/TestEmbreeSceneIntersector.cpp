#include "fixtures/SubdivisionSurfaceMeshFixtures.h"
#include "fixtures/TriangleMeshFixtures.h"
#include "intersectors/embree/EmbreeBvhBuilder.h"
#include "intersectors/embree/EmbreeSceneIntersector.h"
#include "scene/primitives/Sphere.h"
#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include <catch2/catch.hpp>

namespace crayg {

const Ray RAY_WITH_NO_INTERSECTION = Ray({0, 5, 0}, {1, 0, 0});
const Ray RAY_WITH_TRIANGLE_INTERSECTION = Ray({0.75f, 1, 1.5f}, {0, -1, 0});
const Ray RAY_WITH_SUBD_MESH_INTERSECTION = Ray({0.1f, 1, 0}, {0, -1, 0});
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

    SECTION("should find no intersection for empty scene") {
        Scene emptyScene;
        IntersectorFixture fixture(emptyScene);

        auto intersection = fixture.embreeSceneIntersector->intersect(RAY_WITH_NO_INTERSECTION);

        REQUIRE_FALSE(intersection.isValid());
    }

    SECTION("should find no intersection for scene with TriangleMesh and Sphere") {
        IntersectorFixture fixture(scene);

        auto intersection = fixture.embreeSceneIntersector->intersect(RAY_WITH_NO_INTERSECTION);

        REQUIRE_FALSE(intersection.isValid());
    }

    SECTION("should find intersection for Triangle") {
        IntersectorFixture fixture(scene);

        auto intersection = fixture.embreeSceneIntersector->intersect(RAY_WITH_TRIANGLE_INTERSECTION);

        REQUIRE(intersection.isValid());
        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(1.0f));
        auto triangle = dynamic_cast<Triangle *>(intersection.imageable);
        REQUIRE(triangle->faceId == 3);
        REQUIRE(intersection.isOwning == true);
    }

    SECTION("should find intersection for SubdivisionSurfaceMesh") {
        Scene scene;
        auto subdivisionSurfaceMesh = std::make_shared<SubdivisionSurfaceMesh>();
        SubdivisionSurfaceMeshFixtures::createUnitPlane(*subdivisionSurfaceMesh);
        subdivisionSurfaceMesh->tessellate();
        scene.addObject(subdivisionSurfaceMesh);
        IntersectorFixture fixture(scene);

        auto intersection = fixture.embreeSceneIntersector->intersect(RAY_WITH_SUBD_MESH_INTERSECTION);

        REQUIRE(intersection.isValid());
        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(1.0f));
        auto triangle = dynamic_cast<Triangle *>(intersection.imageable);
        REQUIRE(triangle->faceId == 64);
        REQUIRE(intersection.isOwning == true);
    }

    SECTION("should find intersection for Sphere") {
        IntersectorFixture fixture(scene);

        auto intersection = fixture.embreeSceneIntersector->intersect(RAY_WITH_SPHERE_INTERSECTION);

        REQUIRE(intersection.isValid());
        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(1.0f));
        auto sphere = dynamic_cast<Sphere *>(intersection.imageable);
        REQUIRE(sphere->getRadius() == 1.f);
        REQUIRE(intersection.isOwning == false);
    }

    SECTION("should ignore triangle if ray starts at triangle") {
        IntersectorFixture fixture(scene);

        auto intersection = fixture.embreeSceneIntersector->intersect(RAY_ON_TRIANGLE);

        REQUIRE_FALSE(intersection.isValid());
    }
}

TEST_CASE("EmbreeSceneIntersector::isIntersecting") {
    Scene scene;
    auto sphere1 = std::make_shared<Sphere>(Vector3f(0.f, 0.f, 2.f), 1.f);
    scene.addObject(sphere1);

    SECTION("should find intersection for empty scene") {
        Scene emptyScene;
        IntersectorFixture fixture(emptyScene);
        Ray ray({0, 0, 0}, {0, 0, 1});

        REQUIRE_FALSE(fixture.embreeSceneIntersector->isIntersecting(ray, 1.5f));
    }

    SECTION("should find no intersection for empty scene") {
        Scene emptyScene;
        IntersectorFixture fixture(emptyScene);
        Ray ray({0, 0, 0}, {0, 0, 1});

        REQUIRE_FALSE(fixture.embreeSceneIntersector->isIntersecting(ray, 0.5f));
    }
}

}