#include "UsdCameraReader.h"
#include "Logger.h"
#include "basics/Transform.h"
#include "scene/camera/realistic/lensio/LensFileReaderFactory.h"
#include "sceneIO/usd/UsdUtils.h"
#include "utils/Exceptions.h"
#include <pxr/usd/ar/resolver.h>
#include <pxr/usd/ar/resolverContextBinder.h>

namespace crayg {

std::shared_ptr<Camera> UsdCameraReader::read() {
    auto camera = BaseUsdXformableReader<pxr::UsdGeomCamera, Camera>::read();

    camera->setName(this->usdPrim.GetPrim().GetPath().GetString());

    const auto focalLength = UsdUtils::getAttributeValueAs<float>(usdPrim.GetFocalLengthAttr(), this->timeCodeToRead);
    camera->setFocalLength(focalLength);

    const auto filmbackSize =
        UsdUtils::getAttributeValueAs<float>(usdPrim.GetHorizontalApertureAttr(), this->timeCodeToRead);
    camera->setFilmbackSize(filmbackSize);

    const auto cameraType =
        UsdUtils::getAttributeValueAsEnum(usdPrim.GetPrim(), "craygCameraType", CameraType::PINHOLE);
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
    auto cameraLens = lensFileReader->readFile(lensFilePath);
    return std::make_unique<CameraLens>(cameraLens);
}

std::unique_ptr<CameraLens> readEmbeddedLensFile(const pxr::UsdAttribute &lensFileAttribute) {
    auto cameraLensData = lensFileAttribute.GetCustomDataByKey(pxr::TfToken("lens"));

    if (cameraLensData.IsEmpty()) {
        CRAYG_LOG_AND_THROW(std::runtime_error("Could not read embedded lens data, 'lens' value was not authored"));
    }

    if (!cameraLensData.CanCast<pxr::VtDictionary>()) {
        CRAYG_LOG_AND_THROW(std::runtime_error("Could not read embedded lens data, 'lens' value was no VtDictionary"));
    }
    auto lensDict = cameraLensData.Get<pxr::VtDictionary>();

    if (!lensDict["name"].CanCast<std::string>()) {
        CRAYG_LOG_AND_THROW(std::runtime_error("Could not read embedded lens data, 'name' value was no std::string"));
    }
    auto lensName = lensDict["name"].Get<std::string>();

    if (!lensDict["surfaces"].CanCast<pxr::VtArray<pxr::GfVec4f>>()) {
        CRAYG_LOG_AND_THROW(
            std::runtime_error("Could not read embedded lens data, 'surfaces' value was no VtArray<pxr::GfVec4f>"));
    }

    std::vector<LensSurface> surfaces;
    for (auto &el : lensDict["surfaces"].Get<pxr::VtArray<pxr::GfVec4f>>()) {
        surfaces.emplace_back(el[0] * 0.1f, el[1] * 0.1f, el[2], el[3] * 0.1f);
    }

    return std::make_unique<CameraLens>(CameraLensMetadata(lensName), surfaces);
}

void UsdCameraReader::readCameraLens(std::shared_ptr<Camera> &camera) const {
    auto lensFileAttribute = usdPrim.GetPrim().GetAttribute(pxr::TfToken("craygLensFile"));
    if (!lensFileAttribute) {
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("craygLensFile attribute was not authored for camera {}", usdPrim.GetPath());
    }
    auto type = lensFileAttribute.GetTypeName().GetAsToken().GetString();

    auto lensFileAssetPath = UsdUtils::getStaticAttributeValueAs<pxr::SdfAssetPath>(lensFileAttribute);
    auto lensFilePath = lensFileAssetPath.GetResolvedPath().empty() ? lensFileAssetPath.GetAssetPath()
                                                                    : lensFileAssetPath.GetResolvedPath();
    if (!lensFilePath.empty()) {
        camera->lens = std::move(readLensFile(lensFilePath));
        return;
    }

    camera->lens = std::move(readEmbeddedLensFile(lensFileAttribute));
}

}
