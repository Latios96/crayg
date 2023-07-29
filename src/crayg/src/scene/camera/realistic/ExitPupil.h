#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_REALISTIC_EXITPUPIL_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_REALISTIC_EXITPUPIL_H_

#include "basics/Bound2d.h"
#include "basics/Vector2.h"
#include "utils/DtoUtils.h"

namespace crayg {

CRAYG_DTO_2(PositionAndArea, Vector2f, point, float, sampleBoundsArea);

struct ExitPupil {
    std::vector<Bounds2df> pupilBounds;

    PositionAndArea samplePupil(const Vector2f &filmPos, float filmDiagonal) const;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_REALISTIC_EXITPUPIL_H_
