#ifndef CRAYG_SRC_CRAYG_INTEGRATIONTESTS_RENDERUTILS_H_
#define CRAYG_SRC_CRAYG_INTEGRATIONTESTS_RENDERUTILS_H_ \
#include <scene/Scene.h>
#include <Renderer.h>
#include <image/ImageWriter.h>
#include <sceneIO/SceneReaderFactory.h>
#include <image/ImageWriters.h>

namespace crayg {

void renderScene(const std::string &scenePath,
                 const std::string imageOutputPath,
                 const Resolution resolution = Resolution(800, 600));

}
#endif //CRAYG_SRC_CRAYG_INTEGRATIONTESTS_RENDERUTILS_H_
