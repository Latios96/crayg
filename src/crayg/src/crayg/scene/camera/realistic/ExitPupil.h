#pragma once

#include "crayg/foundation/math/geometry/Bound2d.h"
#include "crayg/foundation/math/geometry/Vector2.h"
#include "crayg/foundation/math/geometry/Vector2_formatter.h"
#include "crayg/foundation/objects/DtoUtils.h"

namespace crayg {

CRAYG_DTO_2(PositionAndArea, Vector2f, point, float, sampleBoundsArea);

struct ExitPupil {
    std::vector<Bounds2df> pupilBounds;

    PositionAndArea samplePupil(const Vector2f &filmPos, float filmDiagonal) const;
};

}
