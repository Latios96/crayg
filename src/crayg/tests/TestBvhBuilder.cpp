#include <catch2/catch.hpp>
#include <scene/Scene.h>
#include <intersectors/BvhBuilder.h>

namespace crayg {

TEST_CASE("BvhBuilder/build") {

    SECTION("empty scene should create empty root node") {
        Scene scene;
        BvhBuilder bvhBuilder(scene);
        std::unique_ptr<Bvh> bvh = std::unique_ptr<Bvh>(bvhBuilder.build());

        REQUIRE(*bvh->root == BvhNode(BoundingBox(), nullptr, nullptr, std::vector<Imageable *>()));
    }

    SECTION("single objects should create only root node") {
        Scene scene;
        std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Vector3f(), 1.0f);
        scene.addObject(sphere);
        BvhBuilder bvhBuilder(scene);
        std::unique_ptr<Bvh> bvh = std::unique_ptr<Bvh>(bvhBuilder.build());

        REQUIRE(bvh->root->boundingBox == BoundingBox({-1, -1, -1}, {1, 1, 1}));
        REQUIRE(bvh->root->isLeaf());
        REQUIRE(bvh->root->objects == std::vector<Imageable *>({sphere.get()}));
    }

    SECTION("two objects should get their own node each") {
        Scene scene;
        std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(-1, 0, 0), 1.0f);
        std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector3f(1, 0, 0), 1.0f);
        scene.addObject(sphere1);
        scene.addObject(sphere2);

        BvhBuilder bvhBuilder(scene);
        std::unique_ptr<Bvh> bvh = std::unique_ptr<Bvh>(bvhBuilder.build());

        REQUIRE(bvh->root->boundingBox == BoundingBox({-2, -1, -1}, {2, 1, 1}));
        REQUIRE(!bvh->root->isLeaf());
        REQUIRE(bvh->root->objects.empty());

        REQUIRE(bvh->root->left->boundingBox == BoundingBox({-2, -1, -1}, {0, 1, 1}));
        REQUIRE(bvh->root->left->isLeaf());
        REQUIRE(bvh->root->left->objects == std::vector<Imageable *>({sphere1.get()}));

        REQUIRE(bvh->root->right->boundingBox == BoundingBox({0, -1, -1}, {2, 1, 1}));
        REQUIRE(bvh->root->right->isLeaf());
        REQUIRE(bvh->root->right->objects == std::vector<Imageable *>({sphere2.get()}));
    }

    SECTION("two objects with the same centroid should be placed in the same node") {
        Scene scene;
        std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(1, 0, 0), 1.5f);
        std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector3f(1, 0, 0), 1.0f);
        scene.addObject(sphere1);
        scene.addObject(sphere2);

        BvhBuilder bvhBuilder(scene);
        std::unique_ptr<Bvh> bvh = std::unique_ptr<Bvh>(bvhBuilder.build());

        REQUIRE(bvh->root->boundingBox == BoundingBox({-0.5, -1.5, -1.5}, {2.5, 1.5, 1.5}));
        REQUIRE(bvh->root->isLeaf());
        REQUIRE(bvh->root->objects == std::vector<Imageable *>({sphere1.get(), sphere2.get()}));
    }

    SECTION("three objects should be placed in a hierarchy") {
        Scene scene;
        std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(Vector3f(-1, 0, 0), 1.5f);
        std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector3f(1, 0, 0), 1.0f);
        std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(Vector3f(1, 0, 1), 1.0f);
        scene.addObject(sphere1);
        scene.addObject(sphere2);
        scene.addObject(sphere3);

        BvhBuilder bvhBuilder(scene);
        std::unique_ptr<Bvh> bvh = std::unique_ptr<Bvh>(bvhBuilder.build());

        REQUIRE(!bvh->root->isLeaf());
        REQUIRE(bvh->root->left->isLeaf());
        REQUIRE(bvh->root->left->objects == std::vector<Imageable *>({sphere1.get()}));
        REQUIRE(!bvh->root->right->isLeaf());
        REQUIRE(bvh->root->right->left->isLeaf());
        REQUIRE(bvh->root->right->left->objects == std::vector<Imageable *>({sphere2.get()}));
        REQUIRE(bvh->root->right->right->isLeaf());
        REQUIRE(bvh->root->right->right->objects == std::vector<Imageable *>({sphere3.get()}));
    }

}
}
