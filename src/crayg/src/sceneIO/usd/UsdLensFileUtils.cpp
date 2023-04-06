#include "UsdLensFileUtils.h"
#include "UsdUtils.h"

namespace crayg {

void UsdLensFileUtils::writeEmbeddedLensFile(const CameraLens &cameraLens, pxr::UsdPrim usdCamera) {
    UsdUtils::createAndSetAttribute(usdCamera, "craygLensFile", std::string(""));
    auto craygLensFileAttribute = usdCamera.GetAttribute(pxr::TfToken("craygLensFile"));

    pxr::VtDictionary lensDict;
    lensDict["name"] = cameraLens.name;

    pxr::VtArray<pxr::GfVec4f> elements;
    for (auto &element : cameraLens.elements) {
        elements.push_back({element.curvatureRadius, element.thickness, element.ior, element.apertureRadius});
    }
    lensDict["elements"] = elements;

    craygLensFileAttribute.SetCustomDataByKey(pxr::TfToken("lens"), pxr::VtValue(lensDict));
}
} // crayg