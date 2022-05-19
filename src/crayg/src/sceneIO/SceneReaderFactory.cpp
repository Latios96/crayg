//
// Created by Jan Honsbrok on 25.11.18.
//


#include <boost/filesystem/path.hpp>
#include "SceneReaderFactory.h"
#include "sceneIO/read/usd/UsdSceneReader.h"
#include "Logger.h"

namespace crayg {

std::shared_ptr<SceneReader> SceneReaderFactory::createSceneWriter(std::string scenePath, Scene &scene) {
    boost::filesystem::path path(scenePath);
    std::string extension = path.extension().string();

    if (extension == ".json") {
        return std::shared_ptr<SceneReader>(new JsonSceneReader(scenePath, scene));
    } else if (extension == ".usd") {
        return std::shared_ptr<SceneReader>(new UsdSceneReader(scenePath, scene));
    } else {
        Logger::error("No SceneReader found for extension {}", extension);
        throw std::runtime_error(fmt::format("No SceneReader found for extension {}", extension));
    }
}

}
