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

std::unique_ptr<CameraLens> readLensFile(const std::string &lensFilePath) {
    auto lensFileReader = LensFileReaderFactory::createLensFileReader(lensFilePath);
    auto cameraLens = lensFileReader->readFile();
    return std::make_unique<CameraLens>(cameraLens);
}

std::unique_ptr<CameraLens> readEmbeddedLensFile(const pxr::UsdAttribute &lensFileAttribute) {
    auto cameraLensData = lensFileAttribute.GetCustomDataByKey(pxr::TfToken("lens"));

    if (!cameraLensData.CanCast<pxr::VtDictionary>()) {
        throw std::runtime_error("Could not read embedded lens data, 'lens' value was no VtDictionary");
    }
    auto lensDict = cameraLensData.Get<pxr::VtDictionary>();

    if (!lensDict["name"].CanCast<std::string>()) {
        throw std::runtime_error("Could not read embedded lens data, 'name' value was no std::string");
    }
    auto lensName = lensDict["name"].Get<std::string>();

    if (!lensDict["elements"].CanCast<pxr::VtArray<pxr::GfVec4f>>()) {
        throw std::runtime_error("Could not read embedded lens data, 'elements' value was no VtArray<pxr::GfVec4f>");
    }

    std::vector<LensElement> elements;
    for (auto &el : lensDict["elements"].Get<pxr::VtArray<pxr::GfVec4f>>()) {
        elements.emplace_back(el[0], el[1], el[2], el[3]);
    }

    return std::make_unique<CameraLens>(lensName, elements);
}

void UsdCameraReader::readCameraLens(std::shared_ptr<Camera> &camera) const {
    auto lensFileAttribute = usdPrim.GetPrim().GetAttribute(pxr::TfToken("craygLensFile"));
    if (!lensFileAttribute) {
        throw std::runtime_error(
            fmt::format("craygLensFile attribute was not authored for camera {}", usdPrim.GetPath()));
    }

    auto lensFilePath = UsdUtils::getStaticAttributeValueAs<std::string>(lensFileAttribute);
    if (!lensFilePath.empty()) {
        camera->lens = std::move(readLensFile(lensFilePath));
        return;
    }

    camera->lens = std::move(readEmbeddedLensFile(lensFileAttribute));
}

}
