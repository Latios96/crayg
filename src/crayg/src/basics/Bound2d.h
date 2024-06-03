#pragma once

#include "MathUtils.h"
#include "Vector2.h"
#include "utils/ToStringHelper.h"
#include <fmt/ostream.h>
#include <ostream>

namespace crayg {

template <typename T> class Bounds2d {
  public:
    Bounds2d() : min({std::numeric_limits<T>::max()}), max({std::numeric_limits<T>::lowest()}) {
    }

    Bounds2d(const Vector2<T> &min, const Vector2<T> &max) : min(min), max(max) {
    }

    Bounds2d(const Bounds2d<T> &vec) : min(vec.min), max(vec.max) {
    }

    Vector2<T> min, max;

    template <typename OT> Bounds2d<T> unionWith(const Bounds2d<OT> &other) {
        return {{std::min<T>(min.x, static_cast<T>(other.min.x)), std::min<T>(min.y, static_cast<T>(other.min.y))},
                {std::max<T>(max.x, static_cast<T>(other.max.x)), std::max<T>(max.y, static_cast<T>(other.max.y))}};
    }

    template <typename OT> Bounds2d<T> unionWith(const Vector2<OT> &other) {
        return {{std::min<T>(min.x, static_cast<T>(other.x)), std::min<T>(min.y, static_cast<T>(other.y))},
                {std::max<T>(max.x, static_cast<T>(other.x)), std::max<T>(max.y, static_cast<T>(other.y))}};
    }

    template <typename OT> Bounds2d<T> expand(const Vector2<OT> &other) {
        return {min - other, max + other};
    }

    Vector2<T> lerp(float u, float v) const {
        return {MathUtils::lerp(u, min.x, max.x), MathUtils::lerp(v, min.y, max.y)};
    }

    Vector2<T> diagonal() const {
        return max - min;
    }

    float area() const {
        const auto d = diagonal();
        return (d.x * d.y);
    }

    template <typename OT> bool contains(const Vector2<OT> &other) const {
        return min.x <= other.x && min.y <= other.y && max.x >= other.x && max.y >= other.y;
    }

    bool operator==(const Bounds2d &rhs) const {
        return min == rhs.min && max == rhs.max;
    }

    bool operator!=(const Bounds2d &rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream &operator<<(std::ostream &os, const Bounds2d &d) {
        os << ToStringHelper("Bounds2d").addMember("min", d.min).addMember("max", d.max).finish();
        return os;
    }
};

typedef Bounds2d<float> Bounds2df;
typedef Bounds2d<int> Bounds2di;

}

template <typename T> struct fmt::formatter<crayg::Bounds2d<T>> : ostream_formatter {};
