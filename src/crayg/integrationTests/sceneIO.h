#ifndef CRAYG_SRC_CRAYG_INTEGRATIONTESTS_SCENEIO_H_
#define CRAYG_SRC_CRAYG_INTEGRATIONTESTS_SCENEIO_H_
#include <KnipserTest.h>
#include <vector>
#include <KnipserAssertions.h>
#include <sceneIO/write/SceneWriter.h>
#include <scene/GroundPlane.h>
#include <scene/DiffuseMaterial.h>
#include "renderUtils.h"
#include "sceneIO/write/usd/UsdSceneWriter.h"
#include "sceneIO/SceneWriterFactory.h"

namespace crayg {

std::vector<knipser::KnipserTest> sceneIoTests() {
    return {
        knipser::KnipserTest("sceneWriteReadRendersCorrectly", [](knipser::TestContext &context) {
            context.setImageOutputName("sceneWriteReadRendersCorrectly.png");

            Scene scene;
            scene.renderSettings.resolution = Resolution(800, 600);
            scene.renderSettings.maxSamples = 4;

            std::shared_ptr<Camera>
                camera = std::make_shared<Camera>(Transform(
                Transform::withPosition({0, 0, 10}).matrix * Transform::withRotation(0, 180, 0).matrix), 35.0f, 36.0f);
            scene.camera = camera;

            const std::shared_ptr<Material>
                diffuseMaterial = std::make_shared<DiffuseMaterial>("diffuseMaterial", Color(1, 0, 0));

            const std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Vector3f(0, 0, 0), 1.5f);
            sphere->setMaterial(diffuseMaterial);
            scene.addObject(sphere);

            const std::shared_ptr<Material>
                groundMaterial = std::make_shared<DiffuseMaterial>("groundMaterial", Color(1, 1, 1));

            const std::shared_ptr<GroundPlane> groundPlane = std::make_shared<GroundPlane>();
            groundPlane->setPosition(Vector3f(0, -1.5f, 0));
            groundPlane->setMaterial(groundMaterial);
            scene.addObject(groundPlane);

            auto light = std::make_shared<Light>();
            light->setPosition(Vector3f(0, 3, 3));
            light->setIntensity(3.0);
            scene.addLight(light);

            const std::string scenePath = context.getOutputFolder() + "/writtenScene.usda";
            auto sceneWriter = SceneWriterFactory::createSceneWriter(scenePath, scene);
            sceneWriter->writeScene(scenePath);

            renderScene(scenePath, context.getOutputFilename());

            ASSERT_IMAGES_ARE_EQUAL(context);
        })
    };
}

}
#endif //CRAYG_SRC_CRAYG_INTEGRATIONTESTS_SCENEIO_H_