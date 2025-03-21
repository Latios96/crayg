#include "LensFileExtendedFormatReader.h"
#include "scene/camera/realistic/LensGeometry.h"
#include "scene/camera/realistic/LensMaterial.h"
#include "utils/EnumUtils.h"
#include "utils/Exceptions.h"
#include "utils/utils.h"
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim_all.hpp>
#include <pystring.h>
#include <sstream>

namespace crayg {

enum class ParseState { UNDEFINED, METADATA, SURFACES, ASPHERIC_COEFFICIENTS };

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
        parseState = ParseState::METADATA;
        return true;
    } else if (line == "[surfaces]") {
        parseState = ParseState::SURFACES;
        return true;
    } else if (line == "[aspheric coefficients]") {
        parseState = ParseState::ASPHERIC_COEFFICIENTS;
        return true;
    }
    return false;
}

std::string readMetadataString(const std::string &line, const std::string &token) {
    auto value = line.substr(token.size());
    boost::algorithm::trim_all(value);
    return value;
}

float parseFloat(int lineIndex, const std::string &floatStr, const std::string &name) {
    try {
        return std::stof(floatStr);
    } catch (std::invalid_argument &e) {
        CRAYG_LOG_AND_THROW(InvalidExtendedLensFileFormatException(
            lineIndex, fmt::format("Value '{}' for {} is not a float", floatStr, name)));
    }
}

int parseInt(int lineIndex, const std::string &intStr, const std::string &name) {
    try {
        return std::stoi(intStr);
    } catch (std::invalid_argument &e) {
        CRAYG_LOG_AND_THROW(InvalidExtendedLensFileFormatException(
            lineIndex, fmt::format("Value '{}' for {} is not a int", intStr, name)));
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
        CRAYG_LOG_AND_THROW(InvalidExtendedLensFileFormatException(
            lineIndex, fmt::format("'{}' is an unsupported material value", material)));
    }
    return LensMaterial::createMaterialById(*lensMaterial);
}

LensGeometry parseLensGeometry(int lineIndex, std::string &geometry) {
    boost::algorithm::trim_all(geometry);
    auto lensGeometry = EnumUtils::parse<LensGeometry>(geometry);
    if (!lensGeometry) {
        CRAYG_LOG_AND_THROW(InvalidExtendedLensFileFormatException(
            lineIndex, fmt::format("'{}' is an unsupported LensGeometry", geometry)));
    }
    return *lensGeometry;
}

void parseSurfaceLine(int lineIndex, std::string line, std::vector<LensSurface> &surfaces) {
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

    surfaces.emplace_back(radius * 0.1f, thickness * 0.1f, ior, housingRadius * 0.1f, abbeNumber, lensMaterial,
                          lensGeometry);
}

void checkLensSurfaceIndex(int lineIndex, int indexToCheck, std::vector<LensSurface> &surfaces) {
    if (surfaces.empty()) {
        CRAYG_LOG_AND_THROW(InvalidExtendedLensFileFormatException("[Surfaces] section is empty"));
    } else if (indexToCheck < 0 || indexToCheck >= surfaces.size()) {
        CRAYG_LOG_AND_THROW(InvalidExtendedLensFileFormatException(
            lineIndex, fmt::format("{} is an invalid lens index, valid is [0-{}]", indexToCheck, surfaces.size())));
    }
}

void checkLensGeometry(int lineIndex, int indexToCheck, std::vector<LensSurface> &surfaces) {
    if (surfaces[indexToCheck].geometry != LensGeometry::ASPHERICAL) {
        CRAYG_LOG_AND_THROW(InvalidExtendedLensFileFormatException(
            lineIndex, fmt::format("lens surface {} is not an aspheric lens, it's {}", indexToCheck,
                                   surfaces[indexToCheck].geometry)));
    }
}

void parseAsphericCoefficientsLine(int lineIndex, std::string line, std::vector<LensSurface> &surfaces,
                                   std::vector<AsphericCoefficients> &asphericCoefficients) {

    std::vector<std::string> indexAndCoefficients;
    boost::split(indexAndCoefficients, line, boost::is_any_of(":"));
    if (indexAndCoefficients.size() > 2) {
        CRAYG_LOG_AND_THROW(InvalidExtendedLensFileFormatException(
            lineIndex, fmt::format("'{}' is an invalid aspheric coefficients line", line)));
    }
    if (indexAndCoefficients.size() < 2) {
        CRAYG_LOG_AND_THROW(InvalidExtendedLensFileFormatException(
            lineIndex, fmt::format("'{}' is an incomplete aspheric coefficients line", line)));
    }

    const int lensIndex = parseInt(lineIndex, indexAndCoefficients[0], "Aspheric Lens Index");
    checkLensSurfaceIndex(lineIndex, lensIndex, surfaces);
    checkLensGeometry(lineIndex, lensIndex, surfaces);

    boost::algorithm::trim_all(indexAndCoefficients[1]);
    boost::algorithm::to_lower(indexAndCoefficients[1]);

    std::vector<std::string> coefficientStrs;
    boost::split(coefficientStrs, indexAndCoefficients[1], boost::is_any_of(" "));

    AsphericCoefficients coefficients;

    for (auto &coefficientStr : coefficientStrs) {
        std::vector<std::string> splittedNameAndValue;
        boost::split(splittedNameAndValue, coefficientStr, boost::is_any_of("="));
        if (splittedNameAndValue.size() != 2) {
            CRAYG_LOG_AND_THROW(InvalidExtendedLensFileFormatException(
                lineIndex, fmt::format("'{}' is an invalid coefficient format, only k=v is allowed", coefficientStr)));
        }

        const std::string coefficientName = splittedNameAndValue[0];
        const std::string coefficientValue = splittedNameAndValue[1];

        if (coefficientName == "k") {
            coefficients.k = parseFloat(lineIndex, coefficientValue, "k");
        } else if (coefficientName == "a2") {
            coefficients.a2 = parseFloat(lineIndex, coefficientValue, "a2");
        } else if (coefficientName == "a4") {
            coefficients.a4 = parseFloat(lineIndex, coefficientValue, "a4");
        } else if (coefficientName == "a6") {
            coefficients.a6 = parseFloat(lineIndex, coefficientValue, "a6");
        } else if (coefficientName == "a8") {
            coefficients.a8 = parseFloat(lineIndex, coefficientValue, "a8");
        } else if (coefficientName == "a10") {
            coefficients.a10 = parseFloat(lineIndex, coefficientValue, "a10");
        } else if (coefficientName == "a12") {
            coefficients.a12 = parseFloat(lineIndex, coefficientValue, "a12");
        } else if (coefficientName == "a14") {
            coefficients.a14 = parseFloat(lineIndex, coefficientValue, "a14");
        } else {
            CRAYG_LOG_AND_THROW(InvalidExtendedLensFileFormatException(
                lineIndex, fmt::format("'{}' is an invalid coefficient name", coefficientName)));
        }
    }
    asphericCoefficients.push_back(coefficients);
    surfaces[lensIndex].asphericCoefficientsIndex = asphericCoefficients.size() - 1;
}

CameraLens LensFileExtendedFormatReader::readFileContent(const std::string &content) {
    std::vector<LensSurface> surfaces;
    std::vector<AsphericCoefficients> asphericCoefficients;
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

        const bool metadataWasParsedButNameIsEmpty =
            parseState == ParseState::SURFACES && cameraLensMetadata.name.empty();
        if (metadataWasParsedButNameIsEmpty) {
            CRAYG_LOG_AND_THROW(InvalidExtendedLensFileFormatException("[Metadata] section is missing 'name'"));
        }

        if (parseState == ParseState::METADATA) {
            parseMetadataLine(i, line, cameraLensMetadata);
        } else if (parseState == ParseState::SURFACES) {
            parseSurfaceLine(i, line, surfaces);
        } else if (parseState == ParseState::ASPHERIC_COEFFICIENTS) {
            parseAsphericCoefficientsLine(i, line, surfaces, asphericCoefficients);
        }
    }

    const bool surfacesSectionWasNotFound = parseState == ParseState::METADATA;
    if (surfacesSectionWasNotFound) {
        CRAYG_LOG_AND_THROW(InvalidExtendedLensFileFormatException("[Surfaces] section is missing"));
    }

    const bool surfacesSectionWasEmpty = parseState == ParseState::SURFACES && surfaces.empty();
    if (surfacesSectionWasEmpty) {
        CRAYG_LOG_AND_THROW(InvalidExtendedLensFileFormatException("[Surfaces] section is empty"));
    }

    for (int i = 0; i < surfaces.size(); i++) {
        auto &surface = surfaces[i];
        if (surface.geometry == LensGeometry::ASPHERICAL && !surface.asphericCoefficientsIndex.has_value()) {
            CRAYG_LOG_AND_THROW(InvalidExtendedLensFileFormatException(
                fmt::format("surface {} is aspheric, but has no coefficients", i)));
        }
    }

    return {cameraLensMetadata, surfaces, asphericCoefficients, {}};
}

} // crayg
