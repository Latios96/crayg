#include "SceneReaderFactory.h"
#include "Logger.h"
#include "sceneIO/read/usd/UsdSceneReader.h"
#include "utils/Exceptions.h"
#include <filesystem>

namespace crayg {

std::shared_ptr<SceneReader> SceneReaderFactory::createSceneReader(const std::string &scenePath, Scene &scene,
                                                                   const SceneReader::ReadOptions &readOptions) {
    std::filesystem::path path(scenePath);
    std::string extension = path.extension().string();

    if (extension == ".usd" || extension == ".usda" || extension == ".usdc") {
        return std::shared_ptr<SceneReader>(new UsdSceneReader(scenePath, scene, readOptions));
    } else {
        CRAYG_LOG_AND_THROW(std::runtime_error(fmt::format("No SceneReader found for extension '{}'", extension)));
    }
}

}
