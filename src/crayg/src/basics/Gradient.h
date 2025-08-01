#pragma once

#include "Color.h"
#include "utils/Exceptions.h"
#include "utils/ToStringHelper.h"
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <ostream>
#include <vector>

namespace crayg {

template <typename T> struct GradientStop {
    GradientStop(float position, T value) : position(position), value(value) {
    }

    float position;
    T value;

    bool operator==(const GradientStop &rhs) const {
        return position == rhs.position && value == rhs.value;
    }

    bool operator!=(const GradientStop &rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream &operator<<(std::ostream &os, const GradientStop &stop) {
        os << ToStringHelper("GradientStop")
                  .addMember("position", stop.position)
                  .addMember("value", stop.value)
                  .finish();
        return os;
    }
};

template <typename T> class Gradient {
  public:
    explicit Gradient(const std::vector<T> &values) {
        const float stepSize = 1.0f / static_cast<float>(values.size() - 1);
        for (int i = 0; i < values.size(); i++) {
            float position = stepSize * i;
            if (i == 0) {
                position = 0;
            } else if (i == values.size() - 1) {
                position = 1;
            }
            stops.emplace_back(position, values[i]);
        }
    }

    explicit Gradient(const std::vector<GradientStop<T>> &stops) : stops(stops) {
    }

    T interpolate(float position) const;

  private:
    T lerp(const T &firstValue, const T &secondValue, float position) const;
    std::vector<GradientStop<T>> stops;
};

template <typename T> T Gradient<T>::interpolate(float position) const {
    position = std::clamp<float>(position, 0, 1);

    for (int i = 1; i < stops.size(); i++) {
        const GradientStop<T> &firstStop = stops[i - 1];
        const GradientStop<T> &secondStop = stops[i];

        const bool firstValueIsBeforePosition = firstStop.position <= position;
        const bool secondValueIsAfterPosition = secondStop.position >= position;
        const bool positionIsBetweenStops = firstValueIsBeforePosition && secondValueIsAfterPosition;

        if (positionIsBetweenStops) {
            const float positionInInterval = position - firstStop.position;
            const float relativePositionInInterval = positionInInterval / (secondStop.position - firstStop.position);
            return lerp(firstStop.value, secondStop.value, relativePositionInInterval);
        }
    }

    CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Did not find a stop for position {}", position);
}

template <typename T> T Gradient<T>::lerp(const T &firstValue, const T &secondValue, float position) const {
    return firstValue * (1 - position) + secondValue * position;
}

}

template <typename T> struct fmt::formatter<crayg::Gradient<T>> : ostream_formatter {};

template <typename T> struct fmt::formatter<crayg::GradientStop<T>> : ostream_formatter {};
