#include <tuple>
#include "Color.h"
#include <algorithm>
#include <utils/ToStringHelper.h>

namespace crayg {

std::ostream &operator<<(std::ostream &os, const Color &color) {
    os << ToStringHelper("Color")
        .addMember("r", color.r)
        .addMember("g", color.g)
        .addMember("b", color.b)
        .finish();
    return os;
}

Color::Color() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

Color Color::operator+(const Color &otherColor) const {
    return {r + otherColor.r, g + otherColor.g, b + otherColor.b};
}

Color Color::operator-(const Color &otherColor) const {
    return {r - otherColor.r, g - otherColor.g, b - otherColor.b};
}

Color Color::operator*(const Color &otherColor) const {
    return {r * otherColor.r, g * otherColor.g, b * otherColor.b};
}

Color Color::operator*(float scalar) const {
    return {r * scalar, g * scalar, b * scalar};
}

Color Color::clamp() const {
    return {std::min(1.0f, r), std::min(1.0f, g), std::min(1.0f, b)};
}

std::tuple<int, int, int> Color::getRgbValues() const {
    int int_r = static_cast<int>(std::clamp<float>(r, 0, 1) * 255);
    int int_g = static_cast<int>(std::clamp<float>(g, 0, 1) * 255);
    int int_b = static_cast<int>(std::clamp<float>(b, 0, 1) * 255);
    return std::make_tuple(int_r, int_g, int_b);
}

bool Color::operator==(const Color &color) const {
    return (r == color.r && g == color.g && b == color.b);
}

bool Color::operator!=(const Color &color) const {
    return !(r == color.r && g == color.g && b == color.b);
}

Color Color::operator+(float value) const {
    return {r + value, g + value, b + value};
}
Color Color::operator/(float scalar) const {
    return {r / scalar, g / scalar, b / scalar};
}

}