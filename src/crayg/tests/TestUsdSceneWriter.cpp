#include <catch2/catch.hpp>
#include "scene/Scene.h"
#include "sceneIO/write/usd/UsdSceneWriter.h"
#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdRender/settings.h>
#include <pxr/usd/usdGeom/sphere.h>

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
    UsdSceneWriter usdSceneWriter;

    SECTION("should write camera") {
        usdSceneWriter.writeScene(stage, scene);

        REQUIRE(count<pxr::UsdGeomCamera>(stage) == 1);
    }

    SECTION("should write render settings") {
        usdSceneWriter.writeScene(stage, scene);

        REQUIRE(count<pxr::UsdRenderSettings>(stage) == 1);
    }

    SECTION("should write sphere") {
        scene.addObject(std::make_shared<Sphere>(Vector3f(1, 2, 3), 3));

        usdSceneWriter.writeScene(stage, scene);

        REQUIRE(count<pxr::UsdGeomSphere>(stage) == 1);
    }
}

}