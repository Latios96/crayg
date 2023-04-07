#include "LensFileJsonReader.h"
#include <nlohmann/json.hpp>

namespace crayg {

CameraLens LensFileJsonReader::readFileContent(const std::string &content) {
    auto parsedJson = nlohmann::json::parse(content);
    std::vector<LensElement> elements;

    const std::string name = parsedJson["name"].get<std::string>();
    for (auto &element : parsedJson["elements"]) {
        elements.emplace_back(element["curvatureRadius"].get<float>(), element["thickness"].get<float>(),
                              element["ior"].get<float>(), element["apertureRadius"].get<float>());
    }

    return {name, elements};
}

} // crayg