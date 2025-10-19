#pragma once
#include "crayg/renderer/Renderer.h"
#include "crayg/scene/Scene.h"
#include "crayg/scene/io/SceneReaderFactory.h"

namespace crayg {

void renderScene(const std::string &scenePath, const std::string imageOutputPath,
                 const Resolution resolution = Resolution(800, 600));

}
