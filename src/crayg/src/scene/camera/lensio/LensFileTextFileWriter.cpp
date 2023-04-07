#include "LensFileTextFileWriter.h"

namespace crayg {

std::string LensFileTextFileWriter::writeFileContent(const CameraLens &cameraLens) {
    std::string content;

    if (!cameraLens.name.empty()) {
        content += fmt::format("# {}\n", cameraLens.name);
    }

    content += fmt::format("{}\n", cameraLens.elements.size());

    for (auto &lens : cameraLens.elements) {
        content += fmt::format("{:.5f} {:.5f} {:.5f} {:.5f}\n", lens.curvatureRadius, lens.thickness, lens.ior,
                               lens.apertureRadius, lens.center);
    }

    return content;
}

} // crayg