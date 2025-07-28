#include "LensFileJsonReader.h"
#include <nlohmann/json.hpp>

namespace crayg {

CameraLens LensFileJsonReader::readFileContent(const std::string &content) {
    auto parsedJson = nlohmann::json::parse(content);
    std::vector<LensSurface> surfaces;

    const std::string name = parsedJson["name"].get<std::string>();
    for (auto &surface : parsedJson["surfaces"]) {
        surfaces.emplace_back(surface["curvatureRadius"].get<float>() * 0.1f, surface["thickness"].get<float>() * 0.1f,
                              surface["ior"].get<float>(), surface["apertureRadius"].get<float>() * 0.1f);
    }

    return {CameraLensMetadata(name), surfaces};
}

}