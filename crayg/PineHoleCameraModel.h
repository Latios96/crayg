//
// Created by jan on 16.08.18.
//

#ifndef CRAYG_PINEHOLECAMERAMODEL_H
#define CRAYG_PINEHOLECAMERAMODEL_H


#include "Camera.h"
#include "foundation/Ray.h"

class PineHoleCameraModel {
private:
    Camera &camera;
    float imageRatio;
    float imagePlaneWidth, imagePlaneHeight;
    int imageWidth, imageHeight;

    Vector3f sideVector, upVector, viewVector, planeCenter;

    Vector3f getPixelCenter(float x, float y);

public:
    PineHoleCameraModel(Camera &camera, int imageWidth, int imageHeight);

    Ray createPrimaryRay(float x, float y);
};


#endif //CRAYG_PINEHOLECAMERAMODEL_H
