//
// Created by Jan on 28.10.2021.
//

#include <basics/Transform.h>
#include "CameraTranslator.h"
#include "Conversions.h"
namespace crayg {

CameraTranslator::CameraTranslator(pxr::UsdGeomCamera camera) : usdCamera(camera) {}
std::shared_ptr<Camera> CameraTranslator::translate() {
    pxr::GfMatrix4d matrix;
    bool resetsXformStack = false;
    usdCamera.GetLocalTransformation(&matrix, &resetsXformStack);

    const Vector3f position = Conversions::convert(matrix.ExtractTranslation());
    const Vector3f centerOfInterest = Transform(Conversions::convert(matrix)).apply(Vector3f(0, 0, -1));

    float focalLength, filmbackSize;
    usdCamera.GetFocalLengthAttr().Get(&focalLength);
    usdCamera.GetHorizontalApertureAttr().Get(&filmbackSize);

    return std::make_shared<Camera>(position, Vector3f(0, 1, 0), centerOfInterest, focalLength, filmbackSize);
};

}
