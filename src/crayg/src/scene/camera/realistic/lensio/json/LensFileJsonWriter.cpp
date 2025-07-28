#include "LensFileJsonWriter.h"
#include <nlohmann/json.hpp>

namespace crayg {

std::string LensFileJsonWriter::writeFileContent(const CameraLens &cameraLens) {
    nlohmann::json lensJson = nlohmann::json{};

    auto jsonLensSurfaces = nlohmann::json::array();
    for (auto &surface : cameraLens.surfaces) {
        jsonLensSurfaces.push_back({
            {"curvatureRadius", surface.curvatureRadius * 10},
            {"thickness", surface.thickness * 10},
            {"ior", surface.ior},
            {"apertureRadius", surface.apertureRadius * 10},
        });
    }
    lensJson["name"] = cameraLens.metadata.name;
    lensJson["surfaces"] = jsonLensSurfaces;

    return lensJson.dump(4);
}

}