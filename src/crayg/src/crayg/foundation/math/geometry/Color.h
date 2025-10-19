#pragma once

#include <algorithm>
#include <cmath>
#include <ostream>
#include <tuple>

namespace crayg {

class Color {
  public:
    float r, g, b;

    Color() {
        this->r = 0;
        this->g = 0;
        this->b = 0;
    }

    Color(float r, float g, float b) : r(r), g(g), b(b) {
    }

    explicit Color(float *data) : r(data[0]), g(data[1]), b(data[2]) {
    }

    static Color createGrey(float grey) {
        return {grey, grey, grey};
    }

    static Color createBlack() {
        return {};
    }

    static Color createWhite() {
        return {1, 1, 1};
    }

    static Color createRed() {
        return {1, 0, 0};
    }

    static Color createGreen() {
        return {0, 1, 0};
    }

    static Color createBlue() {
        return {0, 0, 1};
    }

    static Color fromRGB(int r, int g, int b) {
        return {static_cast<float>(r) / 255.f, static_cast<float>(g) / 255.f, static_cast<float>(b) / 255.f};
    }

    static Color createRandom();

    Color operator+(const Color &otherColor) const {
        return {r + otherColor.r, g + otherColor.g, b + otherColor.b};
    }

    Color operator+(float value) const {
        return {r + value, g + value, b + value};
    }

    Color operator-(const Color &otherColor) const {
        return {r - otherColor.r, g - otherColor.g, b - otherColor.b};
    }

    Color operator*(const Color &otherColor) const {
        return {r * otherColor.r, g * otherColor.g, b * otherColor.b};
    }

    Color operator/(const Color &otherColor) const {
        return {r / otherColor.r, g / otherColor.g, b / otherColor.b};
    }

    Color operator*(float scalar) const {
        return {r * scalar, g * scalar, b * scalar};
    }

    Color operator/(float scalar) const {
        return {r / scalar, g / scalar, b / scalar};
    }

    Color &operator+=(const Color &otherColor) {
        r += otherColor.r;
        g += otherColor.g;
        b += otherColor.b;
        return *this;
    }

    Color &operator-=(const Color &otherColor) {
        r -= otherColor.r;
        g -= otherColor.g;
        b -= otherColor.b;
        return *this;
    }

    Color &operator*=(const Color &otherColor) {
        r *= otherColor.r;
        g *= otherColor.g;
        b *= otherColor.b;
        return *this;
    }

    Color &operator/=(const Color &otherColor) {
        r /= otherColor.r;
        g /= otherColor.g;
        b /= otherColor.b;
        return *this;
    }

    Color &operator+=(float scalar) {
        r += scalar;
        g += scalar;
        b += scalar;
        return *this;
    }

    Color &operator-=(float scalar) {
        r -= scalar;
        g -= scalar;
        b -= scalar;
        return *this;
    }

    Color &operator*=(float scalar) {
        r *= scalar;
        g *= scalar;
        b *= scalar;
        return *this;
    }

    Color &operator/=(float scalar) {
        r /= scalar;
        g /= scalar;
        b /= scalar;
        return *this;
    }

    bool operator==(const Color &color) const {
        return (r == color.r && g == color.g && b == color.b);
    }

    bool operator!=(const Color &color) const {
        return !(r == color.r && g == color.g && b == color.b);
    }

    bool operator<(const Color &rhs) const {
        if (r < rhs.r) {
            return true;
        }
        if (rhs.r < r) {
            return false;
        }
        if (g < rhs.g) {
            return true;
        }
        if (rhs.g < g) {
            return false;
        }
        return b < rhs.b;
    }

    bool operator>(const Color &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Color &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Color &rhs) const {
        return !(*this < rhs);
    }

    Color clamp() const {
        return {clampSafe(r), clampSafe(g), clampSafe(b)};
    }

    bool isBlack() const {
        return r == 0 && g == 0 && b == 0;
    }

    bool hasNaN() const {
        return std::isnan(r) || std::isnan(g) || std::isnan(b);
    }

    const float *data() const {
        return &r;
    }

    float *data() {
        return &r;
    }

    std::tuple<int, int, int> getRgbValues() const {
        const Color clamped = clamp();
        int int_r = static_cast<int>(clamped.r * 255);
        int int_g = static_cast<int>(clamped.g * 255);
        int int_b = static_cast<int>(clamped.b * 255);
        return std::make_tuple(int_r, int_g, int_b);
    }

    Color pow(float exponent) const {
        return {std::pow(r, exponent), std::pow(g, exponent), std::pow(b, exponent)};
    }

    friend std::ostream &operator<<(std::ostream &os, const Color &color);

  private:
    static float clampSafe(float value) {
        if (std::isnan(value)) {
            return 0;
        }
        return std::clamp<float>(value, 0, 1);
    }
};

}
