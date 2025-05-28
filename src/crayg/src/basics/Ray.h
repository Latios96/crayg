#pragma once

#include "Vector3f.h"
#include <fmt/ostream.h>
#include <optional>
#include <ostream>

namespace crayg {

struct Ray {
    Vector3f startPoint, direction;
    float length;

  public:
    Ray() = default;

    Ray(Vector3f startPoint, Vector3f direction) {
        this->startPoint = startPoint;
        this->direction = direction;
        this->length = std::numeric_limits<float>::min();
    }

    Ray(Vector3f startPoint, Vector3f direction, float length) {
        this->startPoint = startPoint;
        this->direction = direction;
        this->length = length;
    }

    static Ray createInvalid() {
        return {Vector3f::createInvalid(), Vector3f::createInvalid(), std::numeric_limits<float>::max()};
    }

    bool isValid() {
        return startPoint.isValid() && direction.isValid() && length != std::numeric_limits<float>::max();
    }

    Vector3f constructIntersectionPoint() const {
        return startPoint + (direction * length);
    }

    Vector3f constructIntersectionPoint(float t) const {
        return startPoint + (direction * t);
    }

    Ray offsetStartPointBy(float offset) const {
        return Ray(startPoint + direction * offset, direction, length);
    }

    bool operator==(const Ray &rhs) const {
        return startPoint == rhs.startPoint && direction == rhs.direction && length == rhs.length;
    }

    bool operator!=(const Ray &rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream &operator<<(std::ostream &os, const Ray &ray);
};

}

template <> struct fmt::formatter<crayg::Ray> : ostream_formatter {};
