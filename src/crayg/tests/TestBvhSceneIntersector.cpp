#include <catch2/catch.hpp>
#include <intersectors/naive/NaiveBvhNode.h>
#include <scene/primitives/Sphere.h>
#include <intersectors/naive/NaiveBvhSceneIntersector.h>

namespace crayg {

TEST_CASE("NaiveBvhSceneIntersector/intersect with objects in node") {

    Scene scene;
    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(), 1.0f);
    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector3f(), 1.1f);
    std::vector<Imageable *> objects({sphere1.get(), sphere2.get()});
    auto bvhNode = std::make_unique<NaiveBvhNode>(BoundingBox({-1.1f, -1.1f, -1.1f}, {1.1f, 1.1f, 1.1f}), nullptr, nullptr, objects);
    auto bvh = std::make_unique<NaiveBvh>(std::move(bvhNode));

    SECTION("isIntersecting") {
        NaiveBvhSceneIntersector intersector(scene, std::move(bvh));

        bool result = intersector.isIntersecting({{0.0f, 0.0f, -5.0f}, {0.0f, 0.0f, 1.0f}});

        REQUIRE(result);
    }

    SECTION("intersect") {
        NaiveBvhSceneIntersector intersector(scene, std::move(bvh));

        Imageable::Intersection intersection = intersector.intersect({{0.0f, 0.0f, -5.0f}, {0.0f, 0.0f, 1.0f}});

        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(3.9f));
    }

}

TEST_CASE("NaiveBvhSceneIntersector/intersect with objects in left") {

    Scene scene;
    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(), 1.1f);
    std::vector<Imageable *> objects({sphere1.get()});
    auto left = std::make_unique<NaiveBvhNode>(BoundingBox({-1.1f, -1.1f, -1.1f}, {1.1f, 1.1f, 1.1f}), nullptr, nullptr, objects);
    auto bvhNode = std::make_unique<NaiveBvhNode>(BoundingBox({-1.1f, -1.1f, -1.1f}, {1.1f, 1.1f, 1.1f}),
                                             std::move(left), nullptr, std::vector<Imageable*>());
    auto bvh = std::make_unique<NaiveBvh>(std::move(bvhNode));

    SECTION("isIntersecting") {
        NaiveBvhSceneIntersector intersector(scene, std::move(bvh));

        bool result = intersector.isIntersecting({{0, 0, -5}, {0, 0, 1}});

        REQUIRE(result);
    }

    SECTION("intersect") {
        NaiveBvhSceneIntersector intersector(scene, std::move(bvh));

        Imageable::Intersection intersection = intersector.intersect({{0, 0, -5}, {0, 0, 1}});

        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(3.9f));
    }
}

TEST_CASE("NaiveBvhSceneIntersector/intersect with objects in right") {

    Scene scene;
    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(), 1.1f);
    std::vector<Imageable *> objects({sphere1.get()});
    auto right = std::make_unique<NaiveBvhNode>(BoundingBox({-1.1f, -1.1f, -1.1f}, {1.1f, 1.1f, 1.1f}), nullptr, nullptr, objects);
    auto bvhNode = std::make_unique<NaiveBvhNode>(BoundingBox({-1.1f, -1.1f, -1.1f}, {1.1f, 1.1f, 1.1f}), nullptr, std::move(right), std::vector<Imageable*>());
    auto bvh = std::make_unique<NaiveBvh>(std::move(bvhNode));

    SECTION("isIntersecting") {
        NaiveBvhSceneIntersector intersector(scene, std::move(bvh));

        bool result = intersector.isIntersecting({{0, 0, -5}, {0, 0, 1}});

        REQUIRE(result);
    }

    SECTION("intersect") {
        NaiveBvhSceneIntersector intersector(scene, std::move(bvh));

        Imageable::Intersection intersection = intersector.intersect({{0, 0, -5}, {0, 0, 1}});

        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(3.9f));
    }

}

TEST_CASE("NaiveBvhSceneIntersector/intersect with objects in left and right, left is nearer") {

    Scene scene;
    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(0, 0, -1), 1.0f);
    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector3f(0, 0, 1), 1.0f);
    std::vector<Imageable *> objectsLeft({sphere1.get()});
    std::vector<Imageable *> objectsRight({sphere2.get()});
    auto left = std::make_unique<NaiveBvhNode>(BoundingBox({-1, -1, -2}, {1, 1, 0}), nullptr, nullptr, objectsLeft);
    auto right = std::make_unique<NaiveBvhNode>(BoundingBox({-1, -1, 0}, {1, 1, 2}), nullptr, nullptr, objectsRight);
    auto naiveBvhNode = std::make_unique<NaiveBvhNode>(BoundingBox({-1, -1, -2}, {1, 1, 2}), std::move(left), std::move(right), std::vector<Imageable*>());
    auto naiveBvh = std::make_unique<NaiveBvh>(std::move(naiveBvhNode));

    SECTION("isIntersecting") {
        NaiveBvhSceneIntersector intersector(scene, std::move(naiveBvh));

        bool result = intersector.isIntersecting({{0, 0, -5}, {0, 0, 1}});

        REQUIRE(result);
    }

    SECTION("intersect") {
        NaiveBvhSceneIntersector intersector(scene, std::move(naiveBvh));

        Imageable::Intersection intersection = intersector.intersect({{0, 0, -5}, {0, 0, 1}});

        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(3.0f));
        REQUIRE(intersection.imageable == sphere1.get());
    }
}

TEST_CASE("NaiveBvhSceneIntersector/intersect with objects in left and right, right is nearer") {

    Scene scene;
    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(0, 0, 1), 1.0f);
    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector3f(0, 0, -1), 1.0f);
    std::vector<Imageable *> objectsLeft({sphere1.get()});
    std::vector<Imageable *> objectsRight({sphere2.get()});
    auto left = std::make_unique<NaiveBvhNode>(BoundingBox({-1, -1, 0}, {1, 1, 2}), nullptr, nullptr, objectsRight);
    auto right = std::make_unique<NaiveBvhNode>(BoundingBox({-1, -1, -2}, {1, 1, 0}), nullptr, nullptr, objectsLeft);
    auto bvhNode = std::make_unique<NaiveBvhNode>(BoundingBox({-1, -1, -2}, {1, 1, 2}), std::move(left), std::move(right), std::vector<Imageable*>());
    auto bvh = std::make_unique<NaiveBvh>(std::move(bvhNode));

    SECTION("isIntersecting") {
        NaiveBvhSceneIntersector intersector(scene, std::move(bvh));

        bool result = intersector.isIntersecting({{0, 0, -5}, {0, 0, 1}});

        REQUIRE(result);
    }

    SECTION("intersect") {
        NaiveBvhSceneIntersector intersector(scene, std::move(bvh));

        Imageable::Intersection intersection = intersector.intersect({{0, 0, -5}, {0, 0, 1}});

        REQUIRE(intersection.rayParameter == Catch::Detail::Approx(3.0f));
        REQUIRE(intersection.imageable == sphere2.get());
    }
}

}
