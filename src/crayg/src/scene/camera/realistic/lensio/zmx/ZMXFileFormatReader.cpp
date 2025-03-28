#include "ZMXFileFormatReader.h"

#include "scene/camera/realistic/lensio/LensFileParseUtils.h"

#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim_all.hpp>
#include <pystring.h>

namespace crayg {

class InvalidZMXLineException : public InvalidLensFileException {
  public:
    InvalidZMXLineException(int lineIndex, const std::string &lineType, int expectedValues, int values)
        : InvalidLensFileException(lineIndex, fmt::format("Invalid {} line, expected at least {} values, got {}",
                                                          lineType, expectedValues, values)) {
    }
};

float parseUnitLine(const std::string &line, int lineIndex) {
    std::vector<std::string> parts;
    boost::split(parts, line, boost::is_any_of(" "));

    if (parts.size() < 2) {
        CRAYG_LOG_AND_THROW(InvalidZMXLineException(lineIndex, "UNIT", 2, parts.size()));
    }
    const std::string unit = parts[1];

    if (unit == "MM") {
        return 0.1;
    }
    if (unit == "INCH" || unit == "IN") {
        return 2.54;
    }

    return 1;
}

struct IncompleteLensSurface {
    IncompleteLensSurface() = default;

    int firstLineIndexOfSurface;
    std::optional<float> curvatureRadius;
    std::optional<float> thickness;
    std::optional<float> apertureRadius;
    std::optional<LensMaterial> glass;

    bool isComplete() const {
        return curvatureRadius.has_value() && thickness.has_value() && apertureRadius.has_value();
    }

    std::vector<std::string> getMissingTerms() const {
        std::vector<std::string> missing;

        if (!curvatureRadius) {
            missing.emplace_back("CURV");
        }

        if (!thickness) {
            missing.emplace_back("DISZ");
        }

        if (!apertureRadius) {
            missing.emplace_back("DIAM");
        }

        return missing;
    }

    LensSurface get() const {
        return LensSurface(*curvatureRadius, *thickness, glass->ior, *apertureRadius, glass->abbeNo, *glass,
                           LensGeometry::SPHERICAL);
    }
};

class IncompleteSurfaceException : public InvalidLensFileException {
  public:
    IncompleteSurfaceException(const IncompleteLensSurface &incompleteSurface)
        : InvalidLensFileException(incompleteSurface.firstLineIndexOfSurface,
                                   fmt::format("Defined surface is incomplete, missing terms [{}]",
                                               fmt::join(incompleteSurface.getMissingTerms(), ", "))) {
    }
};

float parseSimpleFloatValueLine(const std::string &line, int lineIndex, const std::string &lineType,
                                const std::string &name) {
    std::vector<std::string> parts;
    boost::split(parts, line, boost::is_any_of(" "));

    if (parts.size() < 2) {
        CRAYG_LOG_AND_THROW(InvalidZMXLineException(lineIndex, lineType, 2, parts.size()));
    }
    const std::string valueStr = parts[1];
    return LensFileParseUtils::parseFloat(lineIndex, valueStr, name);
}

float curvatureToRadius(float curvature) {
    if (curvature != 0) {
        return 1 / curvature;
    }
    return 0;
}

float parseCurvatureLine(const std::string &line, int lineIndex) {
    return parseSimpleFloatValueLine(line, lineIndex, "CURV", "curvature");
}

float parseDiameterLine(const std::string &line, int lineIndex) {
    return parseSimpleFloatValueLine(line, lineIndex, "DIAM", "diameter");
}

float parseDistanceZ(const std::string &line, int lineIndex) {
    return parseSimpleFloatValueLine(line, lineIndex, "DISZ", "distance Z");
}

LensMaterial parseGlass(const std::string &line, int lineIndex) {
    std::vector<std::string> parts;
    boost::split(parts, line, boost::is_any_of(" "));

    if (parts.size() < 6) {
        CRAYG_LOG_AND_THROW(InvalidZMXLineException(lineIndex, "GLAS", 6, parts.size()));
    }

    const std::string &iorStr = parts[4];
    const std::string abbeNoStr = parts[5];

    const auto materialId = LensMaterial::findMaterialIdByName(parts[1]);
    if (materialId) {
        return LensMaterial::createMaterialById(*materialId);
    }

    const float ior = LensFileParseUtils::parseFloat(lineIndex, iorStr, "ior");
    const float abbeNo = LensFileParseUtils::parseFloat(lineIndex, abbeNoStr, "abbeNo");
    return LensMaterial(LensMaterialId::UNKNOWN, ior, abbeNo, {});
}

IncompleteLensSurface parseSurface(const std::vector<std::string> &lines, int lineIndex, int &lastLineOfSurface,
                                   float scale) {
    IncompleteLensSurface incompleteLensSurface;
    incompleteLensSurface.firstLineIndexOfSurface = lineIndex - 1; // lineIndex is index of first line after SURF

    for (int i = lineIndex; i < lines.size(); i++) {
        auto line = lines[i];
        boost::algorithm::trim_all(line);

        if (pystring::startswith(line, "SURF")) {
            lastLineOfSurface = i - 1;
            break;
        }

        if (pystring::startswith(line, "CURV")) {
            incompleteLensSurface.curvatureRadius = curvatureToRadius(parseCurvatureLine(line, i)) * scale;
        }

        if (pystring::startswith(line, "DIAM")) {
            incompleteLensSurface.apertureRadius = parseDiameterLine(line, i) * scale;
        }
        if (pystring::startswith(line, "DISZ")) {
            incompleteLensSurface.thickness = parseDistanceZ(line, i) * scale;
        }

        if (pystring::startswith(line, "GLAS")) {
            LensMaterial glass = parseGlass(line, i);
            incompleteLensSurface.glass = glass;
        }
    }

    if (!incompleteLensSurface.glass) {
        incompleteLensSurface.glass = LensMaterial::createMaterialById(LensMaterialId::AIR);
    }

    return incompleteLensSurface;
}

void removeObjectAndImagePlanes(std::vector<IncompleteLensSurface> &surfaces) {
    const auto isImageOrObjectPlane = [](const IncompleteLensSurface &lensSurface) {
        return lensSurface.curvatureRadius == 0 && lensSurface.glass && lensSurface.glass->ior == 1 &&
               lensSurface.glass->abbeNo == 0;
    };

    if (isImageOrObjectPlane(*surfaces.begin())) {
        surfaces.erase(surfaces.begin());
    }

    if (isImageOrObjectPlane(*--surfaces.end())) {
        surfaces.erase(--surfaces.end());
    }
}

CameraLens ZMXFileFormatReader::readFileContent(const std::string &content) {
    std::vector<IncompleteLensSurface> incompleteLensSurfaces;
    std::vector<AsphericCoefficients> asphericCoefficients;
    VariableLensDistances variableLensDistances;
    std::vector<std::string> lines;
    boost::split(lines, content, boost::is_any_of("\n"));

    CameraLensMetadata cameraLensMetadata;

    float scale = 0.1f;

    for (int i = 0; i < lines.size(); i++) {
        auto &line = lines[i];
        boost::algorithm::trim_all(line);

        if (line.empty()) {
            continue;
        }

        if (pystring::startswith(line, "UNIT")) {
            scale = parseUnitLine(line, i);
        } else if (pystring::startswith(line, "SURF")) {
            int lastLineOfSurface = i;

            auto lensSurface = parseSurface(lines, i + 1, lastLineOfSurface, scale);
            incompleteLensSurfaces.push_back(lensSurface);

            i = lastLineOfSurface;
        }
    }

    if (incompleteLensSurfaces.empty()) {
        CRAYG_LOG_AND_THROW(InvalidLensFileException("No Surfaces are defined"));
    }

    removeObjectAndImagePlanes(incompleteLensSurfaces);

    if (incompleteLensSurfaces.empty()) {
        CRAYG_LOG_AND_THROW(InvalidLensFileException("No Surfaces are defined"));
    }

    std::vector<LensSurface> surfaces;

    for (auto &surface : incompleteLensSurfaces) {
        if (!surface.isComplete()) {
            CRAYG_LOG_AND_THROW(IncompleteSurfaceException(surface));
        }
        surfaces.push_back(surface.get());
    }

    return {cameraLensMetadata, surfaces, asphericCoefficients, variableLensDistances};
}

}
