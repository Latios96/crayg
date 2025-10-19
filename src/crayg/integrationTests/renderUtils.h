#pragma once
#include <renderer/Renderer.h>
#include <scene/Scene.h>
#include <scene/io/SceneReaderFactory.h>

namespace crayg {

void renderScene(const std::string &scenePath, const std::string imageOutputPath,
                 const Resolution resolution = Resolution(800, 600));

}
