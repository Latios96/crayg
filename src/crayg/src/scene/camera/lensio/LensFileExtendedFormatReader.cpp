#include "LensFileExtendedFormatReader.h"
#include "scene/camera/LensGeometry.h"
#include "scene/camera/LensMaterial.h"
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

    InvalidExtendedLensFileFormatException(int lineNumber, const std::string message)
        : runtime_error(fmt::format("Invalid lens file: Line {}: {}", lineNumber, message)) {
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

void parseMetadataLine(const std::string &line, LensFileExtendedFormatReader::ParsedMetadata &parsedMetadata) {
    std::string lowerLine = line;
    boost::algorithm::to_lower(lowerLine);
    if (pystring::startswith(lowerLine, "name:")) {
        auto name = line.substr(5);
        boost::algorithm::trim_all(name);
        parsedMetadata.name = name;
    }
}

float parseFloat(int lineNumber, std::string &floatStr, const std::string &name) {
    try {
        return std::stof(floatStr);
    } catch (std::invalid_argument &e) {
        throw InvalidExtendedLensFileFormatException(lineNumber,
                                                     fmt::format("Value '{}' for {} is not a float", floatStr, name));
    }
}

LensMaterial parseMaterial(int lineNumber, std::string &material) {
    boost::algorithm::trim_all(material);
    auto lensMaterial = EnumUtils::parse<LensMaterial>(material);
    if (!lensMaterial) {
        throw InvalidExtendedLensFileFormatException(lineNumber,
                                                     fmt::format("'{}' is an unsupported material value", material));
    }
    return *lensMaterial;
}

LensGeometry parseLensGeometry(int lineNumber, std::string &geometry) {
    boost::algorithm::trim_all(geometry);
    auto lensGeometry = EnumUtils::parse<LensGeometry>(geometry);
    if (!lensGeometry) {
        throw InvalidExtendedLensFileFormatException(lineNumber,
                                                     fmt::format("'{}' is an unsupported LensGeometry", geometry));
    }
    return *lensGeometry;
}

void parseElementsLine(int lineNumber, std::string line, std::vector<LensElement> &elements) {
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

    float radius = parseFloat(lineNumber, radiusStr, "Radius");
    float thickness = parseFloat(lineNumber, thicknessStr, "Thickness");
    float ior = parseFloat(lineNumber, iorStr, "IOR");
    float housingRadius = parseFloat(lineNumber, housingRadiusStr, "Housing Radius");
    float abbeNumber = parseFloat(lineNumber, abbeNumberStr, "Abbe-No");

    auto lensMaterial = parseMaterial(lineNumber, material);
    auto lensGeometry = parseLensGeometry(lineNumber, geometry);

    elements.emplace_back(radius * 0.1f, thickness * 0.1f, ior, housingRadius * 0.1f, abbeNumber, lensMaterial,
                          lensGeometry);
}

CameraLens LensFileExtendedFormatReader::readFileContent(const std::string &content) {
    std::vector<LensElement> elements;
    std::vector<std::string> lines;
    boost::split(lines, content, boost::is_any_of("\n"));

    ParseState parseState = ParseState::UNDEFINED;
    ParsedMetadata parsedMetadata;

    for (int i = 0; i < lines.size(); i++) {
        auto &line = lines[i];
        line = stripCommentFromLine(line);
        if (line.empty()) {
            continue;
        }

        if (checkLineForStateAndChangeIfNeeded(line, parseState)) {
            continue;
        }

        const bool metadataWasParsedButNameIsEmpty = parseState == ELEMENTS && parsedMetadata.name.empty();
        if (metadataWasParsedButNameIsEmpty) {
            throw InvalidExtendedLensFileFormatException("[Metadata] section is missing 'name'");
        }

        if (parseState == METADATA) {
            parseMetadataLine(line, parsedMetadata);
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

    return {parsedMetadata.name, elements};
}

} // crayg
