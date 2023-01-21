#ifndef CRAYG_COLOR_H
#define CRAYG_COLOR_H

#include <ostream>
#include <tuple>
#include "sampling/Random.h"

namespace crayg {

class Color {
 public:
    float r, g, b;

    Color();

    Color(float r, float g, float b);

    static Color createGrey(float grey) {
        return {grey, grey, grey};
    }

    static Color createBlack() {
        return {};
    }
    static Color createWhite() {
        return {1, 1, 1};
    }

    static Color fromRGB(int r, int g, int b) {
        return {static_cast<float>(r) / 255.f, static_cast<float>(g) / 255.f, static_cast<float>(b) / 255.f};
    }

    static Color createRandom() {
        return {Random::random(),
                Random::random(),
                Random::random()};
    }

    Color operator+(const Color &otherColor) const;

    Color operator+(float value) const;

    Color operator-(const Color &otherColor) const;

    Color operator*(const Color &otherColor) const;

    Color operator*(float scalar) const;

    Color operator/(float scalar) const;

    bool operator==(const Color &color) const;

    bool operator!=(const Color &color) const;

    Color clamp() const;

    bool isBlack()const;

    std::tuple<int, int, int> getRgbValues() const;

    friend std::ostream &operator<<(std::ostream &os, const Color &color);
};

}// namespace crayg
#endif//CRAYG_COLOR_H
