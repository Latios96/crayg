#pragma once

#include "basics/Bound2d.h"
#include "basics/Vector2.h"
#include "basics/Vector2_formatter.h"
#include "utils/DtoUtils.h"

namespace crayg {

CRAYG_DTO_2(PositionAndArea, Vector2f, point, float, sampleBoundsArea);

struct ExitPupil {
    std::vector<Bounds2df> pupilBounds;

    PositionAndArea samplePupil(const Vector2f &filmPos, float filmDiagonal) const;
};

}
