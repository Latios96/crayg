#pragma once
#include <image/io/ImageWriter.h>
#include <image/io/ImageWriters.h>
#include <renderer/Renderer.h>
#include <scene/Scene.h>
#include <sceneIO/SceneReaderFactory.h>

namespace crayg {

void renderScene(const std::string &scenePath, const std::string imageOutputPath,
                 const Resolution resolution = Resolution(800, 600));

}
