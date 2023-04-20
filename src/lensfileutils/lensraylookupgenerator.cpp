#include "scene/camera/RealisticCameraModel.h"
#include "scene/camera/lensio/LensFileReaderFactory.h"
#include "scene/camera/lookup/LensRayLookupTable.h"

int main() {

    const std::string lensFilePath = "C:\\workspace\\crayg\\src\\crayg\\lensProfiling\\lensfiles\\canon-zoom-70.json";
    auto lensFileReader = crayg::LensFileReaderFactory::createLensFileReader(lensFilePath);
    auto cameraLens = lensFileReader->readFile(lensFilePath);
    const auto resolution = crayg::Resolution(1280, 720);
    crayg::Camera camera;
    camera.setFStop(2.8);
    camera.setFocusDistance(130.961);
    camera.lens = std::make_unique<crayg::CameraLens>(cameraLens);
    crayg::RealisticCameraModel realisticCameraModel(camera, resolution);
    realisticCameraModel.init();

    crayg::LensRayLookupTable lensRayLookupTable(resolution, 8);
    lensRayLookupTable.generate(realisticCameraModel);

    lensRayLookupTable.write("C:\\workspace\\crayg\\src\\crayg\\lensProfiling\\lensfiles\\canon-zoom-70.raylookup");
    return 0;
}