#include "LensFileTextFileWriter.h"

namespace crayg {

std::string LensFileTextFileWriter::writeFileContent(const CameraLens &cameraLens) {
    std::string content;

    if (!cameraLens.metadata.name.empty()) {
        content += fmt::format("# {}\n", cameraLens.metadata.name);
    }

    content += fmt::format("{}\n", cameraLens.surfaces.size());

    for (auto &lens : cameraLens.surfaces) {
        content += fmt::format("{:.5f} {:.5f} {:.5f} {:.5f}\n", lens.curvatureRadius * 10, lens.thickness * 10,
                               lens.ior, lens.apertureRadius * 20);
    }

    return content;
}

}