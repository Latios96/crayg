#include "CLI/CLI.hpp"
#include "CraygInfo.h"
#include "Logger.h"
#include "scene/camera/lensio/LensFileReaderFactory.h"
#include "sceneIO/usd/UsdLensFileUtils.h"
#include "sceneIO/usd/UsdUtils.h"

#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/camera.h>

namespace crayg {

void embeddLensFiles(const std::string &stagePath) {
    auto usdStage = pxr::UsdStage::Open(stagePath);

    for (auto prim : usdStage->TraverseAll()) {
        if (!prim.IsA<pxr::UsdGeomCamera>()) {
            continue;
        }
        auto cameraType = UsdUtils::getAttributeValueAsEnum<CameraType>(prim, "craygCameraType", CameraType::PINE_HOLE);
        if (cameraType != CameraType::REALISTIC) {
            continue;
        }
        auto lensFile =
            UsdUtils::getStaticAttributeValueAs<std::string>(prim.GetAttribute(pxr::TfToken("craygLensFile")));
        if (lensFile.empty()) {
            continue;
        }
        auto cameraLensReader = LensFileReaderFactory::createLensFileReader(lensFile);
        auto cameraLens = cameraLensReader->readFile(lensFile);
        UsdLensFileUtils::writeEmbeddedLensFile(cameraLens, prim);
        Logger::info("Embedded lens file for camera {}", prim.GetPath());
    }
    usdStage->Save();
}

}

int main(int argc, char **argv) {
    crayg::Logger::initialize();
    try {
        CLI::App app{fmt::format("Crayg lensfileembedder utils {}, commit {}", crayg::CraygInfo::VERSION,
                                 crayg::CraygInfo::COMMIT_HASH),
                     "lensfileutils"};

        std::string usdStagePath;
        app.add_option("-s,--stage", usdStagePath, "USD stage to embedd lens files for")->required();

        app.parse(argc, argv);

        crayg::embeddLensFiles(usdStagePath);

    } catch (std::exception &e) {
        crayg::Logger::error("Caught exception: {}", e.what());
        return -1;
    }
};