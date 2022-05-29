//
// Created by Jan Honsbrok on 25.11.18.
//


#include <boost/filesystem/path.hpp>
#include "SceneReaderFactory.h"
#include "sceneIO/read/usd/UsdSceneReader.h"
#include "Logger.h"

namespace crayg {

std::shared_ptr<SceneReader> SceneReaderFactory::createSceneReader(std::string scenePath,
                                                                   Scene &scene,
                                                                   const SceneReader::ReadOptions &readOptions) {
    boost::filesystem::path path(scenePath);
    std::string extension = path.extension().string();

    if (extension == ".json") {
        return std::shared_ptr<SceneReader>(new JsonSceneReader(scenePath, scene, readOptions));
    } else if (extension == ".usd" || extension == ".usda" || extension == ".usdc") {
        return std::shared_ptr<SceneReader>(new UsdSceneReader(scenePath, scene, readOptions));
    } else {
        Logger::error("No SceneReader found for extension {}", extension);
        throw std::runtime_error(fmt::format("No SceneReader found for extension {}", extension));
    }
}

}
