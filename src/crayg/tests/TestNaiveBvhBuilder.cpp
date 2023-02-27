#include "scene/primitives/Sphere.h"
#include <catch2/catch.hpp>
#include <intersectors/naive/NaiveBvhBuilder.h>
#include <scene/Scene.h>

namespace crayg {

TEST_CASE("NaiveBvhBuilder/build") {

    SECTION("empty scene should create empty root node") {
        Scene scene;
        NaiveBvhBuilder naiveBvhBuilder(scene);
        std::unique_ptr<NaiveBvh> naiveBvh = std::unique_ptr<NaiveBvh>(naiveBvhBuilder.build());

        REQUIRE(*naiveBvh->root == NaiveBvhNode(BoundingBox(), nullptr, nullptr, std::vector<Imageable *>()));
    }

    SECTION("single objects should create only root node") {
        Scene scene;
        std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Vector3f(), 1.0f);
        scene.addObject(sphere);
        NaiveBvhBuilder naiveBvhBuilder(scene);
        std::unique_ptr<NaiveBvh> naiveBvh = std::unique_ptr<NaiveBvh>(naiveBvhBuilder.build());

        REQUIRE(naiveBvh->root->boundingBox == BoundingBox({-1, -1, -1}, {1, 1, 1}));
        REQUIRE(naiveBvh->root->isLeaf());
        REQUIRE(naiveBvh->root->objects == std::vector<Imageable *>({sphere.get()}));
    }

    SECTION("two objects should get their own node each") {
        Scene scene;
        std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(-1, 0, 0), 1.0f);
        std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector3f(1, 0, 0), 1.0f);
        scene.addObject(sphere1);
        scene.addObject(sphere2);

        NaiveBvhBuilder bvhBuilder(scene);
        std::unique_ptr<NaiveBvh> naiveBvh = std::unique_ptr<NaiveBvh>(bvhBuilder.build());

        REQUIRE(naiveBvh->root->boundingBox == BoundingBox({-2, -1, -1}, {2, 1, 1}));
        REQUIRE(!naiveBvh->root->isLeaf());
        REQUIRE(naiveBvh->root->objects.empty());

        REQUIRE(naiveBvh->root->left->boundingBox == BoundingBox({-2, -1, -1}, {0, 1, 1}));
        REQUIRE(naiveBvh->root->left->isLeaf());
        REQUIRE(naiveBvh->root->left->objects == std::vector<Imageable *>({sphere1.get()}));

        REQUIRE(naiveBvh->root->right->boundingBox == BoundingBox({0, -1, -1}, {2, 1, 1}));
        REQUIRE(naiveBvh->root->right->isLeaf());
        REQUIRE(naiveBvh->root->right->objects == std::vector<Imageable *>({sphere2.get()}));
    }

    SECTION("two objects with the same centroid should be placed in the same node") {
        Scene scene;
        std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(1, 0, 0), 1.5f);
        std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector3f(1, 0, 0), 1.0f);
        scene.addObject(sphere1);
        scene.addObject(sphere2);

        NaiveBvhBuilder naiveBvhBuilder(scene);
        std::unique_ptr<NaiveBvh> naiveBvh = std::unique_ptr<NaiveBvh>(naiveBvhBuilder.build());

        REQUIRE(naiveBvh->root->boundingBox == BoundingBox({-0.5, -1.5, -1.5}, {2.5, 1.5, 1.5}));
        REQUIRE(naiveBvh->root->isLeaf());
        REQUIRE(naiveBvh->root->objects == std::vector<Imageable *>({sphere1.get(), sphere2.get()}));
    }

    SECTION("three objects should be placed in a hierarchy") {
        Scene scene;
        std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(-1, 0, 0), 1.5f);
        std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector3f(1, 0, 0), 1.0f);
        std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(Vector3f(1, 0, 1), 1.0f);
        scene.addObject(sphere1);
        scene.addObject(sphere2);
        scene.addObject(sphere3);

        NaiveBvhBuilder naiveBvhBuilder(scene);
        std::unique_ptr<NaiveBvh> naiveBvh = std::unique_ptr<NaiveBvh>(naiveBvhBuilder.build());

        REQUIRE(!naiveBvh->root->isLeaf());
        REQUIRE(naiveBvh->root->left->isLeaf());
        REQUIRE(naiveBvh->root->left->objects == std::vector<Imageable *>({sphere1.get()}));
        REQUIRE(!naiveBvh->root->right->isLeaf());
        REQUIRE(naiveBvh->root->right->left->isLeaf());
        REQUIRE(naiveBvh->root->right->left->objects == std::vector<Imageable *>({sphere2.get()}));
        REQUIRE(naiveBvh->root->right->right->isLeaf());
        REQUIRE(naiveBvh->root->right->right->objects == std::vector<Imageable *>({sphere3.get()}));
    }
}
}
