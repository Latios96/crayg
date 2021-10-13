//
// Created by Jan on 13.10.2021.
//
#include <catch2/catch.hpp>
#include <scene/Scene.h>
#include <intersectors/BvhBuilder.h>

namespace crayg {

TEST_CASE("BvhBuilder/build") {

    SECTION("empty scene should create empty root node") {
        Scene scene;
        BvhBuilder bvhBuilder(scene);
        std::unique_ptr<BvhNode> root = std::unique_ptr<BvhNode>(bvhBuilder.build());

        REQUIRE(*root == BvhNode(BoundingBox(), nullptr, nullptr, std::vector<SceneObject *>()));
    }

    SECTION("single objects should create only root node") {
        Scene scene;
        std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Vector3f(), 1);
        scene.addObject(sphere);
        BvhBuilder bvhBuilder(scene);
        std::unique_ptr<BvhNode> root = std::unique_ptr<BvhNode>(bvhBuilder.build());

        REQUIRE(root->boundingBox == BoundingBox({-1, -1, -1}, {1, 1, 1}));
        REQUIRE(root->isLeaf());
        REQUIRE(root->objects == std::vector<SceneObject *>({sphere.get()}));
    }

    SECTION("two objects should get their own node each") {
        Scene scene;
        std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(-1, 0, 0), 1);
        std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector3f(1, 0, 0), 1);
        scene.addObject(sphere1);
        scene.addObject(sphere2);

        BvhBuilder bvhBuilder(scene);
        std::unique_ptr<BvhNode> root = std::unique_ptr<BvhNode>(bvhBuilder.build());

        REQUIRE(root->boundingBox == BoundingBox({-2, -1, -1}, {2, 1, 1}));
        REQUIRE(!root->isLeaf());
        REQUIRE(root->objects.empty());

        REQUIRE(root->left->boundingBox == BoundingBox({-2, -1, -1}, {0, 1, 1}));
        REQUIRE(root->left->isLeaf());
        REQUIRE(root->left->objects == std::vector<SceneObject *>({sphere1.get()}));

        REQUIRE(root->right->boundingBox == BoundingBox({0, -1, -1}, {2, 1, 1}));
        REQUIRE(root->right->isLeaf());
        REQUIRE(root->right->objects == std::vector<SceneObject *>({sphere2.get()}));
    }

    SECTION("two objects with the same centroid should be placed in the same node") {
        Scene scene;
        std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(1, 0, 0), 1.5);
        std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector3f(1, 0, 0), 1);
        scene.addObject(sphere1);
        scene.addObject(sphere2);

        BvhBuilder bvhBuilder(scene);
        std::unique_ptr<BvhNode> root = std::unique_ptr<BvhNode>(bvhBuilder.build());

        REQUIRE(root->boundingBox == BoundingBox({-0.5, -1.5, -1.5}, {2.5, 1.5, 1.5}));
        REQUIRE(root->isLeaf());
        REQUIRE(root->objects == std::vector<SceneObject *>({sphere1.get(), sphere2.get()}));
    }

    SECTION("three objects should be placed in a hierarchy") {
        Scene scene;
        std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(-1, 0, 0), 1.5);
        std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector3f(1, 0, 0), 1);
        std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(Vector3f(1, 0, 1), 1);
        scene.addObject(sphere1);
        scene.addObject(sphere2);
        scene.addObject(sphere3);

        BvhBuilder bvhBuilder(scene);
        std::unique_ptr<BvhNode> root = std::unique_ptr<BvhNode>(bvhBuilder.build());

        REQUIRE(!root->isLeaf());
        REQUIRE(root->left->isLeaf());
        REQUIRE(root->left->objects == std::vector<SceneObject *>({sphere1.get()}));
        REQUIRE(!root->right->isLeaf());
        REQUIRE(root->right->left->isLeaf());
        REQUIRE(root->right->left->objects == std::vector<SceneObject *>({sphere2.get()}));
        REQUIRE(root->right->right->isLeaf());
        REQUIRE(root->right->right->objects == std::vector<SceneObject *>({sphere3.get()}));
    }

}
}
