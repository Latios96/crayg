#include "crayg/renderer/integrators/DebugIntegrator.h"
#include "crayg/renderer/intersectors/SceneIntersector.h"
#include "crayg/scene/Scene.h"
#include "crayg/scene/primitives/Sphere.h"
#include <catch2/catch.hpp>
#include <fakeit.hpp>

namespace crayg {

TEST_CASE("DebugIntegrator::integrate") {
    Scene scene;
    fakeit::Mock<SceneIntersector> mockSceneIntersector;

    SECTION("should return simple shading for hit") {
        std::unique_ptr<Sphere> sphere = std::make_unique<Sphere>(Vector3f(), 1.0f);
        auto testData = GENERATE(table<Vector3f, Color>(
            {{{0, 0, -5}, Color::createGrey(1)}, {{-1, 0, -5}, Color::createGrey(0.97014254f)}}));
        fakeit::When(Method(mockSceneIntersector, intersect)).Return(Imageable::Intersection(1, sphere.get()));
        fakeit::Fake((mockSceneIntersector.dtor()));
        auto sceneIntersector = std::shared_ptr<SceneIntersector>(&mockSceneIntersector.get());
        DebugIntegrator debugIntegrator(scene, sceneIntersector);

        Color integratedColor = debugIntegrator.integrate(Ray(std::get<0>(testData), {0, 0, 1}), 0, RayType::CAMERA);

        REQUIRE(integratedColor == std::get<1>(testData));
    }

    SECTION("should return black for no hit") {
        fakeit::When(Method(mockSceneIntersector, intersect)).Return(Imageable::Intersection::createInvalid());
        fakeit::Fake((mockSceneIntersector.dtor()));
        auto sceneIntersector = std::shared_ptr<SceneIntersector>(&mockSceneIntersector.get());
        DebugIntegrator debugIntegrator(scene, sceneIntersector);

        Color integratedColor = debugIntegrator.integrate(Ray({0, 0, 0}, {0, 0, 1}), 0, RayType::CAMERA);

        REQUIRE(integratedColor == Color::createBlack());
    }
}

}