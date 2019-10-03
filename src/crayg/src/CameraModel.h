//
// Created by Jan Honsbrok on 10.11.18.
//

#ifndef CRAYG_CAMERAMODEL_H
#define CRAYG_CAMERAMODEL_H

#include <foundation/Ray.h>

class CameraModel {
 public:
    virtual Ray createPrimaryRay(float x, float y) = 0;

    virtual ~CameraModel() = default;
};
#endif //CRAYG_CAMERAMODEL_H
