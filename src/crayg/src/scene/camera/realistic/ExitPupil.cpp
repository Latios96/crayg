#include "ExitPupil.h"
#include "sampling/Random.h"

namespace crayg {

PositionAndArea ExitPupil::samplePupil(const Vector2f &filmPos, float filmDiagonal) const {
    const float distanceFromFilmCenter = filmPos.length();
    int boundsIndex = distanceFromFilmCenter / (filmDiagonal / 2) * pupilBounds.size();
    boundsIndex = std::min<int>(pupilBounds.size() - 1, boundsIndex);
    const auto pupil = pupilBounds[boundsIndex];

    const float sinTheta = (distanceFromFilmCenter != 0) ? filmPos.y / distanceFromFilmCenter : 0;
    const float cosTheta = (distanceFromFilmCenter != 0) ? filmPos.x / distanceFromFilmCenter : 1;
    auto pLens = pupil.lerp(Random::random(), Random::random());
    const Vector2f point = {cosTheta * pLens.x - sinTheta * pLens.y, sinTheta * pLens.x + cosTheta * pLens.y};
    return {point, pupil.area()};
}

}