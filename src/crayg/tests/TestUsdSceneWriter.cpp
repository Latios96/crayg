#include <catch2/catch.hpp>
#include "scene/Scene.h"
#include "sceneIO/write/usd/UsdSceneWriter.h"
#include "scene/lights/RectLight.h"
#include "scene/lights/DiskLight.h"
#include "scene/primitives/Sphere.h"
#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdRender/settings.h>
#include <pxr/usd/usdGeom/sphere.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdLux/sphereLight.h>
#include <pxr/usd/usdLux/rectLight.h>
#include <pxr/usd/usdLux/diskLight.h>

namespace crayg {

template<typename T>
int count(pxr::UsdStagePtr stage) {
    int count = 0;

    for (auto prim: stage->TraverseAll()) {
        if (prim.IsA<T>()) {
            count++;
        }
    }

    return count;
}

TEST_CASE("UsdSceneWriter::write") {

    Scene scene;
    scene.camera = std::make_shared<Camera>(Transform::withPosition({1, 2, 3}),
                                            50.0f,
                                            35.0f);

    auto stage = pxr::UsdStage::CreateInMemory();
    UsdSceneWriter usdSceneWriter(scene);

    SECTION("should write camera") {
        usdSceneWriter.writeScene(stage);

        REQUIRE(count<pxr::UsdGeomCamera>(stage) == 1);
    }

    SECTION("should not crash when there is no camera") {
        scene.camera = nullptr;
        usdSceneWriter.writeScene(stage);

        REQUIRE(count<pxr::UsdGeomCamera>(stage) == 0);
    }

    SECTION("should write render settings") {
        usdSceneWriter.writeScene(stage);

        REQUIRE(count<pxr::UsdRenderSettings>(stage) == 1);
    }

    SECTION("should write sphere") {
        scene.addObject(std::make_shared<Sphere>(Vector3f(1, 2, 3), 3.0f));

        usdSceneWriter.writeScene(stage);

        REQUIRE(count<pxr::UsdGeomSphere>(stage) == 1);
    }

    SECTION("should write point light") {
        scene.addLight(std::make_shared<Light>(Transform::withPosition({1, 2, -3}), 3.0f));

        usdSceneWriter.writeScene(stage);

        REQUIRE(count<pxr::UsdLuxSphereLight>(stage) == 1);
    }

    SECTION("should write rect light") {
        scene.addLight(std::make_shared<RectLight>(Transform::withPosition({1, 2, -3}), 3.0f, 4.0f, 5.0f));

        usdSceneWriter.writeScene(stage);

        REQUIRE(count<pxr::UsdLuxRectLight>(stage) == 1);
    }

    SECTION("should write disk light") {
        scene.addLight(std::make_shared<DiskLight>(Transform::withPosition({1, 2, -3}), 3.0f, 4.0f));

        usdSceneWriter.writeScene(stage);

        REQUIRE(count<pxr::UsdLuxDiskLight>(stage) == 1);
    }

    SECTION("should write trianglemesh") {
        scene.addObject(std::make_shared<TriangleMesh>());

        usdSceneWriter.writeScene(stage);

        REQUIRE(count<pxr::UsdGeomMesh>(stage) == 1);
    }

    SECTION("should write subd surface mesh") {
        scene.addObject(std::make_shared<SubdivisionSurfaceMesh>());

        usdSceneWriter.writeScene(stage);

        REQUIRE(count<pxr::UsdGeomMesh>(stage) == 1);
    }
}

}