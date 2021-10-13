#include <catch2/catch.hpp>
#include <intersectors/BvhNode.h>
#include <scene/Sphere.h>
#include <intersectors/BvhSceneIntersector.h>

namespace crayg {

TEST_CASE("BvhSceneIntersector/intersect with objects in node") {

    Scene scene;
    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(), 1.0f);
    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector3f(), 1.1f);
    std::vector<SceneObject *> objects({sphere1.get(), sphere2.get()});
    auto *bvhNode = new BvhNode(BoundingBox({-1.1f, -1.1f, -1.1f}, {1.1f, 1.1f, 1.1f}), nullptr, nullptr, objects);

    SECTION("isIntersecting") {
        BvhSceneIntersector intersector(scene, bvhNode);

        bool result = intersector.isIntersecting({{0.0f, 0.0f, -5.0f}, {0.0f, 0.0f, 1.0f}});

        REQUIRE(result);
    }

    SECTION("intersect") {
        BvhSceneIntersector intersector(scene, bvhNode);

        Imageable::Intersection intersection = intersector.intersect({{0.0f, 0.0f, -5.0f}, {0.0f, 0.0f, 1.0f}});

        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(3.9f));
    }

}

TEST_CASE("BvhSceneIntersector/intersect with objects in left") {

    Scene scene;
    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(), 1.1f);
    std::vector<SceneObject *> objects({sphere1.get()});
    auto *left = new BvhNode(BoundingBox({-1.1f, -1.1f, -1.1f}, {1.1f, 1.1f, 1.1f}), nullptr, nullptr, objects);
    auto *bvhNode = new BvhNode(BoundingBox({-1.1f, -1.1f, -1.1f}, {1.1f, 1.1f, 1.1f}), left, nullptr, {});

    SECTION("isIntersecting") {
        BvhSceneIntersector intersector(scene, bvhNode);

        bool result = intersector.isIntersecting({{0, 0, -5}, {0, 0, 1}});

        REQUIRE(result);
    }

    SECTION("intersect") {
        BvhSceneIntersector intersector(scene, bvhNode);

        Imageable::Intersection intersection = intersector.intersect({{0, 0, -5}, {0, 0, 1}});

        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(3.9f));
    }
}

TEST_CASE("BvhSceneIntersector/intersect with objects in right") {

    Scene scene;
    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(), 1.1f);
    std::vector<SceneObject *> objects({sphere1.get()});
    auto *right = new BvhNode(BoundingBox({-1.1f, -1.1f, -1.1f}, {1.1f, 1.1f, 1.1f}), nullptr, nullptr, objects);
    auto *bvhNode = new BvhNode(BoundingBox({-1.1f, -1.1f, -1.1f}, {1.1f, 1.1f, 1.1f}), nullptr, right, {});

    SECTION("isIntersecting") {
        BvhSceneIntersector intersector(scene, bvhNode);

        bool result = intersector.isIntersecting({{0, 0, -5}, {0, 0, 1}});

        REQUIRE(result);
    }

    SECTION("intersect") {
        BvhSceneIntersector intersector(scene, bvhNode);

        Imageable::Intersection intersection = intersector.intersect({{0, 0, -5}, {0, 0, 1}});

        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(3.9f));
    }

}

TEST_CASE("BvhSceneIntersector/intersect with objects in left and right, left is nearer") {

    Scene scene;
    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(0, 0, -1), 1);
    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector3f(0, 0, 1), 1);
    std::vector<SceneObject *> objectsLeft({sphere1.get()});
    std::vector<SceneObject *> objectsRight({sphere2.get()});
    auto *left = new BvhNode(BoundingBox({-1, -1, -2}, {1, 1, 0}), nullptr, nullptr, objectsLeft);
    auto *right = new BvhNode(BoundingBox({-1, -1, 0}, {1, 1, 2}), nullptr, nullptr, objectsRight);
    auto *bvhNode = new BvhNode(BoundingBox({-1, -1, -2}, {1, 1, 2}), left, right, {});

    SECTION("isIntersecting") {
        BvhSceneIntersector intersector(scene, bvhNode);

        bool result = intersector.isIntersecting({{0, 0, -5}, {0, 0, 1}});

        REQUIRE(result);
    }

    SECTION("intersect") {
        BvhSceneIntersector intersector(scene, bvhNode);

        Imageable::Intersection intersection = intersector.intersect({{0, 0, -5}, {0, 0, 1}});

        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(3.0f));
        REQUIRE(intersection.imageable == sphere1);
    }
}

TEST_CASE("BvhSceneIntersector/intersect with objects in left and right, right is nearer") {

    Scene scene;
    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(0, 0, 1), 1);
    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector3f(0, 0, -1), 1);
    std::vector<SceneObject *> objectsLeft({sphere1.get()});
    std::vector<SceneObject *> objectsRight({sphere2.get()});
    auto *left = new BvhNode(BoundingBox({-1, -1, 0}, {1, 1, 2}), nullptr, nullptr, objectsRight);
    auto *right = new BvhNode(BoundingBox({-1, -1, -2}, {1, 1, 0}), nullptr, nullptr, objectsLeft);
    auto *bvhNode = new BvhNode(BoundingBox({-1, -1, -2}, {1, 1, 2}), left, right, {});

    SECTION("isIntersecting") {
        BvhSceneIntersector intersector(scene, bvhNode);

        bool result = intersector.isIntersecting({{0, 0, -5}, {0, 0, 1}});

        REQUIRE(result);
    }

    SECTION("intersect") {
        BvhSceneIntersector intersector(scene, bvhNode);

        Imageable::Intersection intersection = intersector.intersect({{0, 0, -5}, {0, 0, 1}});

        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(3.0f));
        REQUIRE(intersection.imageable == sphere2);
    }
}

}
