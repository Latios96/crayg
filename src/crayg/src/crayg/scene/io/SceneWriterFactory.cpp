#include "SceneWriterFactory.h"
#include "crayg/foundation/exceptions/Exceptions.h"
#include "crayg/foundation/logging/Logger.h"
#include "crayg/scene/io/write/usd/UsdSceneWriter.h"
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