#pragma once
#include "basics/Vector2.h"

#include <optional>
#include <vector>

namespace crayg {

class ApertureShape {
  public:
    ApertureShape() = default;
    float getRadius() const;
    std::optional<int> getSides() const;
    void setRadius(float radius);
    void setSides(const std::optional<int> &sides);

    bool isRoundAperture() const;
    Vector2f samplePoint() const;
    bool pointExceedsAperture(const Vector2f &point) ;

  private:
    void buildPolygons();
    float radius;
    std::optional<int> sides;
    std::vector<Vector2f> bladePolygons;
};

}