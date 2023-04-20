#ifndef CRAYG_SRC_CRAYG_SRC_BASICS_VECTOR2_H_
#define CRAYG_SRC_CRAYG_SRC_BASICS_VECTOR2_H_

#include "utils/ToStringHelper.h"
#include <fmt/ostream.h>
#include <ostream>

namespace crayg {
template <typename T> class Vector2 {
  public:
    T x, y;

    Vector2() : x(0), y(0) {
    }

    explicit Vector2(T val) : x(val), y(val) {
    }

    Vector2(T x, T y) : x(x), y(y) {
    }

    Vector2(const Vector2<T> &vec) : x(vec.x), y(vec.y) {
    }

    template <typename OT> Vector2<T> operator+(const Vector2<OT> &otherVector) const {
        return {x + otherVector.x, y + otherVector.y};
    }

    template <typename OT> Vector2<T> operator-(const Vector2<OT> &otherVector) const {
        return {x - otherVector.x, y - otherVector.y};
    }

    template <typename OT> Vector2<T> operator*(OT scalar) const {
        return {x * scalar, y * scalar};
    }

    template <typename OT> Vector2<T> operator/(OT scalar) const {
        return {x / scalar, y / scalar};
    }

    float length() const {
        return sqrt(std::pow<float>(static_cast<float>(x), 2) + std::pow<float>(static_cast<float>(y), 2));
    }

    float lengthSquared() const {
        return std::pow<float>(static_cast<float>(x), 2) + std::pow<float>(static_cast<float>(y), 2);
    }

    bool operator==(const Vector2<T> &rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator!=(const Vector2<T> &rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector2<T> &f) {
        os << ToStringHelper("Vector2").addMember("x", f.x).addMember("y", f.y).finish();
        return os;
    }
};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;

}

template <typename T> struct fmt::formatter<crayg::Vector2<T>> : ostream_formatter {};

#endif // CRAYG_SRC_CRAYG_SRC_BASICS_VECTOR2_H_
