#include "LensFileExtendedFormatWriter.h"
#include <tabulate/table.hpp>

namespace crayg {
void writeMetadata(std::string &content, const std::string &key, float value) {
    content += fmt::format("{}: {:.3}\n", key, value);
}

void writeMetadata(std::string &content, const std::string &key, const std::string &value) {
    if (value.empty()) {
        return;
    }
    content += fmt::format("{}: {}\n", key, value);
}

std::string formatFloat(float t) {
    return fmt::format("{:.3}", t);
}

void writeSurfaces(std::string &content, const CameraLens &cameraLens) {
    content += "[Surfaces]\n";

    tabulate::Table styled_table;
    styled_table.format().border("").border_left("").corner("").padding_left(0);
    styled_table.add_row({"Radius", "Thickness", "IOR", "Housing-Radius", "Abbe-No", "Material", "Geometry"});
    for (auto &surface : cameraLens.surfaces) {
        styled_table.add_row({formatFloat(surface.curvatureRadius * 10), formatFloat(surface.thickness * 10),
                              formatFloat(surface.ior), formatFloat(surface.apertureRadius * 10),
                              formatFloat(surface.abbeNumber), fmt::format("{}", surface.material.id),
                              fmt::format("{}", surface.geometry)});
    }

    content += styled_table.str();
}

void writeAsphericSurfaces(std::string &content, const CameraLens &cameraLens) {
    content += "\n[Aspheric Coefficients]\n";
    for (int i = 0; i < cameraLens.surfaces.size(); i++) {
        const auto &surface = cameraLens.surfaces[i];
        if (surface.geometry == LensGeometry::ASPHERICAL) {
            const AsphericCoefficients &asphericCoefficients =
                cameraLens.asphericCoefficients[*surface.asphericCoefficientsIndex];
            content += fmt::format("{}: k={} a2={} a4={} a6={} a8={} a10={} a12={} a14={}", i, asphericCoefficients.k,
                                   asphericCoefficients.a2, asphericCoefficients.a4, asphericCoefficients.a6,
                                   asphericCoefficients.a8, asphericCoefficients.a10, asphericCoefficients.a12,
                                   asphericCoefficients.a14);
        }
    }
}

void writeVariableDistances(std::string &content, const CameraLens &cameraLens) {
    content += "\n[Variable Distances]\n";

    content +=
        fmt::format("Focal Length Samples: {}\n", fmt::join(cameraLens.variableLensDistances.sampledFocalLengths, " "));

    for (auto &sampledDistance : cameraLens.variableLensDistances.sampledDistances) {
        content += fmt::format("{}: ", sampledDistance.surfaceIndex);
        for (auto sample : sampledDistance.samples) {
            content += formatFloat(sample * 10) + " ";
        }
        content += "\n";
    }
}

std::string LensFileExtendedFormatWriter::writeFileContent(const CameraLens &cameraLens) {
    std::string content;

    content += "[Metadata]\n";
    writeMetadata(content, "Name", cameraLens.metadata.name);
    writeMetadata(content, "Focal Length", cameraLens.metadata.focalLength * 10);
    writeMetadata(content, "Maximum F Number", cameraLens.metadata.maximumAperture);
    writeMetadata(content, "Squeeze", cameraLens.metadata.squeeze);
    writeMetadata(content, "Surface Count", cameraLens.metadata.surfaceCount);
    writeMetadata(content, "Patent", cameraLens.metadata.patent);
    writeMetadata(content, "Description", cameraLens.metadata.description);

    writeSurfaces(content, cameraLens);

    if (cameraLens.hasAsphericSurfaces()) {
        writeAsphericSurfaces(content, cameraLens);
    }

    if (cameraLens.hasVariableDistances()) {
        writeVariableDistances(content, cameraLens);
    }

    return content;
}
} // crayg