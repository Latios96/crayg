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

std::string LensFileExtendedFormatWriter::writeFileContent(const CameraLens &cameraLens) {
    std::string content;

    content += "[Metadata]\n";
    writeMetadata(content, "Name", cameraLens.metadata.name);
    writeMetadata(content, "Focal Length", cameraLens.metadata.focalLength * 10);
    writeMetadata(content, "Maximum F Number", cameraLens.metadata.maximumAperture);
    writeMetadata(content, "Squeeze", cameraLens.metadata.squeeze);
    writeMetadata(content, "Elements Count", cameraLens.metadata.elementCount);
    writeMetadata(content, "Patent", cameraLens.metadata.patent);
    writeMetadata(content, "Description", cameraLens.metadata.description);

    content += "[Elements]\n";

    tabulate::Table styled_table;
    styled_table.format().border("").border_left("").corner("").padding_left(0);
    styled_table.add_row({"Radius", "Thickness", "IOR", "Housing-Radius", "Abbe-No", "Material", "Geometry"});
    for (auto &element : cameraLens.elements) {
        styled_table.add_row({formatFloat(element.curvatureRadius * 10), formatFloat(element.thickness * 10),
                              formatFloat(element.ior), formatFloat(element.apertureRadius * 10),
                              formatFloat(element.abbeNumber), fmt::format("{}", element.material),
                              fmt::format("{}", element.geometry)});
    }

    content += styled_table.str();

    return content;
}
} // crayg