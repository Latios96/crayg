#ifndef CRAYG_SRC_CRAYG_INTEGRATIONTESTS_RENDERUTILS_H_
#define CRAYG_SRC_CRAYG_INTEGRATIONTESTS_RENDERUTILS_H_
#include <image/io/ImageWriter.h>
#include <image/io/ImageWriters.h>
#include <renderer/Renderer.h>
#include <scene/Scene.h>
#include <sceneIO/SceneReaderFactory.h>

namespace crayg {

void renderScene(const std::string &scenePath, const std::string imageOutputPath,
                 const Resolution resolution = Resolution(800, 600));

}
#endif // CRAYG_SRC_CRAYG_INTEGRATIONTESTS_RENDERUTILS_H_
