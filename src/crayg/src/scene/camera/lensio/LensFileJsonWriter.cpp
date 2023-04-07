#include "LensFileJsonWriter.h"
#include <nlohmann/json.hpp>

namespace crayg {

std::string LensFileJsonWriter::writeFileContent(const CameraLens &cameraLens) {
    nlohmann::json lensJson = nlohmann::json{};

    auto jsonLensElements = nlohmann::json::array();
    for (auto &element : cameraLens.elements) {
        jsonLensElements.push_back({
            {"curvatureRadius", element.curvatureRadius * 10},
            {"thickness", element.thickness * 10},
            {"ior", element.ior},
            {"apertureRadius", element.apertureRadius * 10},
        });
    }
    lensJson["name"] = cameraLens.name;
    lensJson["elements"] = jsonLensElements;

    return lensJson.dump(4);
}

} // crayg