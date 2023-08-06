#include "LensFileExtendedFormatReader.h"
#include "scene/camera/realistic/LensGeometry.h"
#include "scene/camera/realistic/LensMaterial.h"
#include "utils/EnumUtils.h"
#include "utils/utils.h"
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim_all.hpp>
#include <pystring.h>
#include <sstream>

namespace crayg {

enum ParseState { UNDEFINED, METADATA, ELEMENTS };

class InvalidExtendedLensFileFormatException : public std::runtime_error {
  public:
    explicit InvalidExtendedLensFileFormatException(const std::string message)
        : runtime_error(fmt::format("Invalid lens file: {}", message)) {
    }

    InvalidExtendedLensFileFormatException(int lineIndex, const std::string message)
        : runtime_error(fmt::format("Invalid lens file: Line {}: {}", lineIndex + 1, message)) {
    }
};

bool checkLineForStateAndChangeIfNeeded(std::string line, ParseState &parseState) {
    boost::algorithm::to_lower(line);
    if (line == "[metadata]") {
        parseState = METADATA;
        return true;
    } else if (line == "[elements]") {
        parseState = ELEMENTS;
        return true;
    }
    return false;
}

std::string readMetadataString(const std::string &line, const std::string &token) {
    auto value = line.substr(token.size());
    boost::algorithm::trim_all(value);
    return value;
}

float parseFloat(int lineIndex, std::string &floatStr, const std::string &name) {
    try {
        return std::stof(floatStr);
    } catch (std::invalid_argument &e) {
        throw InvalidExtendedLensFileFormatException(lineIndex,
                                                     fmt::format("Value '{}' for {} is not a float", floatStr, name));
    }
}

void parseMetadataLine(int lineIndex, const std::string &line, CameraLensMetadata &parsedMetadata) {
    static std::string nameToken = "name:";
    static std::string maximumFNumberToken = "maximum f number:";
    static std::string patentToken = "patent:";
    static std::string descriptionToken = "description:";

    std::string lowerLine = line;
    boost::algorithm::to_lower(lowerLine);
    if (pystring::startswith(lowerLine, nameToken)) {
        parsedMetadata.name = readMetadataString(line, nameToken);
    } else if (pystring::startswith(lowerLine, maximumFNumberToken)) {
        std::string maxFNumberStr = readMetadataString(line, maximumFNumberToken);
        parsedMetadata.maximumAperture = parseFloat(lineIndex, maxFNumberStr, "Maximum F Number");
    } else if (pystring::startswith(lowerLine, patentToken)) {
        parsedMetadata.patent = readMetadataString(line, patentToken);
    } else if (pystring::startswith(lowerLine, descriptionToken)) {
        parsedMetadata.description = readMetadataString(line, descriptionToken);
    }
}

LensMaterial parseMaterial(int lineIndex, std::string &material) {
    boost::algorithm::trim_all(material);
    auto lensMaterial = EnumUtils::parse<LensMaterialId>(material);
    if (!lensMaterial) {
        throw InvalidExtendedLensFileFormatException(lineIndex,
                                                     fmt::format("'{}' is an unsupported material value", material));
    }
    return LensMaterial::createMaterialById(*lensMaterial);
}

LensGeometry parseLensGeometry(int lineIndex, std::string &geometry) {
    boost::algorithm::trim_all(geometry);
    auto lensGeometry = EnumUtils::parse<LensGeometry>(geometry);
    if (!lensGeometry) {
        throw InvalidExtendedLensFileFormatException(lineIndex,
                                                     fmt::format("'{}' is an unsupported LensGeometry", geometry));
    }
    return *lensGeometry;
}

void parseElementsLine(int lineIndex, std::string line, std::vector<LensElement> &elements) {
    boost::algorithm::to_lower(line);
    if (pystring::startswith(line, "radius")) {
        return;
    }

    std::istringstream iss(line);

    std::string radiusStr, thicknessStr, iorStr, housingRadiusStr, abbeNumberStr;
    std::string material, geometry;
    iss >> radiusStr;
    iss >> thicknessStr;
    iss >> iorStr;
    iss >> housingRadiusStr;
    iss >> abbeNumberStr;
    iss >> material;
    iss >> geometry;

    float radius = parseFloat(lineIndex, radiusStr, "Radius");
    float thickness = parseFloat(lineIndex, thicknessStr, "Thickness");
    float ior = parseFloat(lineIndex, iorStr, "IOR");
    float housingRadius = parseFloat(lineIndex, housingRadiusStr, "Housing Radius");
    float abbeNumber = parseFloat(lineIndex, abbeNumberStr, "Abbe-No");

    auto lensMaterial = parseMaterial(lineIndex, material);
    auto lensGeometry = parseLensGeometry(lineIndex, geometry);

    elements.emplace_back(radius * 0.1f, thickness * 0.1f, ior, housingRadius * 0.1f, abbeNumber, lensMaterial,
                          lensGeometry);
}

CameraLens LensFileExtendedFormatReader::readFileContent(const std::string &content) {
    std::vector<LensElement> elements;
    std::vector<std::string> lines;
    boost::split(lines, content, boost::is_any_of("\n"));

    ParseState parseState = ParseState::UNDEFINED;
    CameraLensMetadata cameraLensMetadata;

    for (int i = 0; i < lines.size(); i++) {
        auto &line = lines[i];
        line = stripCommentFromLine(line);
        if (line.empty()) {
            continue;
        }

        if (checkLineForStateAndChangeIfNeeded(line, parseState)) {
            continue;
        }

        const bool metadataWasParsedButNameIsEmpty = parseState == ELEMENTS && cameraLensMetadata.name.empty();
        if (metadataWasParsedButNameIsEmpty) {
            throw InvalidExtendedLensFileFormatException("[Metadata] section is missing 'name'");
        }

        if (parseState == METADATA) {
            parseMetadataLine(i, line, cameraLensMetadata);
        } else if (parseState == ELEMENTS) {
            parseElementsLine(i, line, elements);
        }
    }

    const bool elementsSectionWasNotFound = parseState == METADATA;
    if (elementsSectionWasNotFound) {
        throw InvalidExtendedLensFileFormatException("[Elements] section is missing");
    }

    const bool elementsSectionWasEmpty = parseState == ELEMENTS && elements.empty();
    if (elementsSectionWasEmpty) {
        throw InvalidExtendedLensFileFormatException("[Elements] section is empty");
    }

    return {cameraLensMetadata, elements};
}

} // crayg
