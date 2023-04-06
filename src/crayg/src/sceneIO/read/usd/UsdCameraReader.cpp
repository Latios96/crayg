#include "UsdCameraReader.h"
#include "Logger.h"
#include "basics/Transform.h"
#include "scene/camera/lensio/LensFileReaderFactory.h"
#include "sceneIO/usd/UsdUtils.h"
#include <pxr/usd/ar/resolver.h>
#include <pxr/usd/ar/resolverContextBinder.h>

namespace crayg {

std::shared_ptr<Camera> UsdCameraReader::read() {
    auto camera = BaseUsdXformableReader<pxr::UsdGeomCamera, Camera>::read();

    const auto focalLength = UsdUtils::getAttributeValueAs<float>(usdPrim.GetFocalLengthAttr(), this->timeCodeToRead);
    camera->setFocalLength(focalLength);

    const auto filmbackSize =
        UsdUtils::getAttributeValueAs<float>(usdPrim.GetHorizontalApertureAttr(), this->timeCodeToRead);
    camera->setFilmbackSize(filmbackSize);

    const auto cameraType =
        UsdUtils::getAttributeValueAsEnum(usdPrim.GetPrim(), "craygCameraType", CameraType::PINE_HOLE);
    camera->setCameraType(cameraType);

    if (cameraType == CameraType::REALISTIC) {
        readCameraLens(camera);
    }

    const auto focusDistance =
        UsdUtils::getAttributeValueAs<float>(usdPrim.GetFocusDistanceAttr(), this->timeCodeToRead);
    camera->setFocusDistance(focusDistance);

    const auto fStop = UsdUtils::getAttributeValueAs<float>(usdPrim.GetFStopAttr(), this->timeCodeToRead);
    camera->setFStop(fStop);

    return camera;
}

UsdCameraReader::UsdCameraReader(const pxr::UsdGeomCamera &camera) : BaseUsdXformableReader(camera) {
}

std::string UsdCameraReader::getTranslatedType() {
    return "camera";
};

void UsdCameraReader::readCameraLens(std::shared_ptr<Camera> &camera) const {
    auto lensFileAttribute = usdPrim.GetPrim().GetAttribute(pxr::TfToken("craygLensFile"));
    if (!lensFileAttribute) {
        throw std::runtime_error(
            fmt::format("craygLensFile attribute was not authored for camera {}", usdPrim.GetPath()));
    }

    auto lensFilePath = UsdUtils::getStaticAttributeValueAs<std::string>(lensFileAttribute);
    if (!lensFilePath.empty()) {
        auto lensFileReader = LensFileReaderFactory::createLensFileReader(lensFilePath);
        auto cameraLens = lensFileReader->readFile();
        camera->lens = std::make_unique<CameraLens>(cameraLens);
        return;
    }
    // try to read embedded lens
}

}
