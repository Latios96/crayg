#include "SceneWriterFactory.h"
#include "sceneIO/write/usd/UsdSceneWriter.h"
#include <boost/filesystem/path.hpp>

namespace crayg {
std::shared_ptr<SceneWriter> SceneWriterFactory::createSceneWriter(std::string scenePath, Scene &scene) {
    boost::filesystem::path path(scenePath);
    std::string extension = path.extension().string();

    if (extension == ".usd" || extension == ".usda" || extension == ".usdc") {
        return std::shared_ptr<SceneWriter>(new UsdSceneWriter(scene));
    } else {
        Logger::error("No SceneWriter found for extension {}", extension);
        throw std::runtime_error(fmt::format("No SceneWriter found for extension {}", extension));
    }
}
} // crayg