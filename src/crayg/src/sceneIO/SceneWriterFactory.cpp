#include "SceneWriterFactory.h"
#include "Logger.h"
#include "sceneIO/write/usd/UsdSceneWriter.h"
#include "utils/Exceptions.h"
#include <filesystem>

namespace crayg {

std::shared_ptr<SceneWriter> SceneWriterFactory::createSceneWriter(std::string scenePath, Scene &scene) {
    std::filesystem::path path(scenePath);
    std::string extension = path.extension().string();

    if (extension == ".usd" || extension == ".usda" || extension == ".usdc") {
        return std::shared_ptr<SceneWriter>(new UsdSceneWriter(scene));
    } else {
        Logger::error("No SceneWriter found for extension {}", extension);
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("No SceneWriter found for extension {}", extension);
    }
}
}