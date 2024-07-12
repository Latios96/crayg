#include "UsdLensFileUtils.h"
#include "UsdUtils.h"

namespace crayg {

void UsdLensFileUtils::writeEmbeddedLensFile(const CameraLens &cameraLens, pxr::UsdPrim usdCamera) {
    UsdUtils::createAndSetAttribute(usdCamera, "craygLensFile", pxr::SdfAssetPath());
    auto craygLensFileAttribute = usdCamera.GetAttribute(pxr::TfToken("craygLensFile"));

    pxr::VtDictionary lensDict;
    lensDict["name"] = cameraLens.metadata.name;

    pxr::VtArray<pxr::GfVec4f> surfaces;
    for (auto &surface : cameraLens.surfaces) {
        surfaces.push_back(
            {surface.curvatureRadius * 10, surface.thickness * 10, surface.ior, surface.apertureRadius * 10});
    }
    lensDict["surfaces"] = surfaces;

    craygLensFileAttribute.SetCustomDataByKey(pxr::TfToken("lens"), pxr::VtValue(lensDict));
}
} // crayg