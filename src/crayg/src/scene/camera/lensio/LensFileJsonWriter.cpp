#include "LensFileJsonWriter.h"
#include <nlohmann/json.hpp>

namespace crayg {

std::string LensFileJsonWriter::writeFileContent(const CameraLens &cameraLens) {
    nlohmann::json lensJson = nlohmann::json{};

    auto jsonLensElements = nlohmann::json::array();
    for (auto &element : cameraLens.elements) {
        jsonLensElements.push_back({
            {"curvatureRadius", element.curvatureRadius},
            {"thickness", element.thickness},
            {"ior", element.ior},
            {"apertureRadius", element.apertureRadius},
        });
    }
    lensJson["name"] = cameraLens.name;
    lensJson["elements"] = jsonLensElements;

    return lensJson.dump(4);
}

} // crayg