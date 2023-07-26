#include "UsdLensFileUtils.h"
#include "UsdUtils.h"

namespace crayg {

void UsdLensFileUtils::writeEmbeddedLensFile(const CameraLens &cameraLens, pxr::UsdPrim usdCamera) {
    UsdUtils::createAndSetAttribute(usdCamera, "craygLensFile", pxr::SdfAssetPath());
    auto craygLensFileAttribute = usdCamera.GetAttribute(pxr::TfToken("craygLensFile"));

    pxr::VtDictionary lensDict;
    lensDict["name"] = cameraLens.metadata.name;

    pxr::VtArray<pxr::GfVec4f> elements;
    for (auto &element : cameraLens.elements) {
        elements.push_back(
            {element.curvatureRadius * 10, element.thickness * 10, element.ior, element.apertureRadius * 10});
    }
    lensDict["elements"] = elements;

    craygLensFileAttribute.SetCustomDataByKey(pxr::TfToken("lens"), pxr::VtValue(lensDict));
}
} // crayg