//
// Created by Jan on 31.10.2020.
//

#ifndef CRAYG_SRC_CRAYG_INTEGRATIONTESTS_SCENEIO_H_
#define CRAYG_SRC_CRAYG_INTEGRATIONTESTS_SCENEIO_H_
#include <KnipserTest.h>
#include <vector>
#include <KnipserAssertions.h>
#include <sceneIO/write/SceneWriter.h>
#include <scene/GroundPlane.h>
#include <scene/DiffuseMaterial.h>
#include <scene/PointLight.h>
#include "renderUtils.h"

std::vector<knipser::KnipserTest> sceneIoTests() {
    return {
        knipser::KnipserTest("sceneWriteReadRendersCorrectly", [](knipser::TestContext &context) {
            context.setImageOutputName("sceneWriteReadRendersCorrectly.png");

            Scene scene;
            scene.renderSettings.resolution = Resolution(800, 600);
            scene.renderSettings.maxSamples = 4;

            std::shared_ptr<Camera>
                camera = std::make_shared<Camera>(Vector3f(0, 0, 10), Vector3f(0, 1, 0), Vector3f(0, 0, -1), 35, 36);
            scene.camera = camera;

            const std::shared_ptr<Material>
                diffuseMaterial = std::make_shared<DiffuseMaterial>("diffuseMaterial", Color(1, 0, 0));

            const std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Vector3f(0, 0, 0), 1.5);
            sphere->setMaterial(diffuseMaterial);
            scene.addObject(sphere);

            const std::shared_ptr<GroundPlane> groundPlane = std::make_shared<GroundPlane>();
            groundPlane->setPosition(Vector3f(0, -1.5f, 0));
            scene.addObject(groundPlane);

            auto light = std::make_shared<PointLight>();
            light->setPosition(Vector3f(0, 3, 3));
            light->setIntensity(1.0);
            scene.addLight(light);

            const std::string scenePath = context.getOutputFolder() + "/writtenScene.json";
            const std::shared_ptr<std::ofstream> ostream = std::make_shared<std::ofstream>(scenePath);
            JsonSerializer jsonSerializer(ostream);
            SceneWriter sceneWriter(scene, jsonSerializer);
            sceneWriter.write();
            ostream->close();

            renderScene(scenePath, context.getOutputFilename());

            ASSERT_IMAGES_ARE_EQUAL(context);
        })
    };
}
#endif //CRAYG_SRC_CRAYG_INTEGRATIONTESTS_SCENEIO_H_