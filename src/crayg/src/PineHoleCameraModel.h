//
// Created by jan on 16.08.18.
//

#ifndef CRAYG_PINEHOLECAMERAMODEL_H
#define CRAYG_PINEHOLECAMERAMODEL_H

#include "scene/Camera.h"
#include "foundation/Ray.h"
#include "CameraModel.h"

// todo add tests
class PineHoleCameraModel : public CameraModel {
 private:
    Camera &camera;
    float imageRatio;
    float imagePlaneWidth, imagePlaneHeight;
    int imageWidth, imageHeight;

    Vector3f sideVector, upVector, viewVector, planeCenter;

    Vector3f getPixelCenter(float x, float y);

 public:
    PineHoleCameraModel(Camera &camera, int imageWidth, int imageHeight);

    Ray createPrimaryRay(float x, float y) override;
};

#endif //CRAYG_PINEHOLECAMERAMODEL_H
