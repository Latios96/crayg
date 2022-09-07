#ifndef CRAYG_SRC_CRAYG_INTEGRATIONTESTS_SCENEIO_CPP_
#define CRAYG_SRC_CRAYG_INTEGRATIONTESTS_SCENEIO_CPP_
#include "renderUtils.h"
#include "sceneIO/SceneWriterFactory.h"
#include "sceneIO/write/usd/UsdSceneWriter.h"
#include "utils.h"
#include <catch2/catch.hpp>
#include <scene/materials/UsdPreviewSurface.h>
#include <scene/primitives/GroundPlane.h>
#include <sceneIO/write/SceneWriter.h>

namespace crayg {

TEST_CASE("SceneIO/sceneWriteReadRendersCorrectly") {
  Scene scene;
  scene.renderSettings.resolution = Resolution(800, 600);
  scene.renderSettings.maxSamples = 4;

  std::shared_ptr<Camera> camera = std::make_shared<Camera>(
      Transform(Transform::withPosition({0, 0, 10}).matrix *
                Transform::withRotation(0, 180, 0).matrix),
      35.0f, 36.0f);
  scene.camera = camera;

    const std::shared_ptr<Material> diffuseMaterial =
        std::make_shared<UsdPreviewSurface>("diffuseMaterial", Color(1, 0, 0));

  const std::shared_ptr<Sphere> sphere =
      std::make_shared<Sphere>(Vector3f(0, 0, 0), 1.5f);
  sphere->setMaterial(diffuseMaterial);
  scene.addObject(sphere);

    const std::shared_ptr<Material> groundMaterial =
        std::make_shared<UsdPreviewSurface>("groundMaterial", Color(1, 1, 1));

  const std::shared_ptr<GroundPlane> groundPlane =
      std::make_shared<GroundPlane>();
  groundPlane->setPosition(Vector3f(0, -1.5f, 0));
  groundPlane->setMaterial(groundMaterial);
  scene.addObject(groundPlane);

  auto light = std::make_shared<Light>();
  light->setPosition(Vector3f(0, 3, 3));
  light->setIntensity(3.0);
  scene.addLight(light);

  const std::string scenePath =
      getOutputFilename("SceneIO", "sceneWriteReadRendersCorrectly", ".usda");
  auto sceneWriter = SceneWriterFactory::createSceneWriter(scenePath, scene);
  sceneWriter->writeScene(scenePath);

  renderScene(
      scenePath,
      getOutputFilename("SceneIO", "sceneWriteReadRendersCorrectly", ".png"));
}

} // namespace crayg
#endif // CRAYG_SRC_CRAYG_INTEGRATIONTESTS_SCENEIO_CPP_