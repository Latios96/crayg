#include "Color.h"
#include "sampling/Random.h"
#include <algorithm>
#include <tuple>
#include <utils/ToStringHelper.h>

namespace crayg {

std::ostream &operator<<(std::ostream &os, const Color &color) {
    os << ToStringHelper("Color").addMember("r", color.r).addMember("g", color.g).addMember("b", color.b).finish();
    return os;
}

Color::Color() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {
}

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

float clampSafe(float value) {
    if (std::isnan(value)) {
        return 0;
    }
    return std::clamp<float>(value, 0, 1);
}

Color Color::clamp() const {
    return {clampSafe(r), clampSafe(g), clampSafe(b)};
}

std::tuple<int, int, int> Color::getRgbValues() const {
    const Color clamped = clamp();
    int int_r = static_cast<int>(clamped.r * 255);
    int int_g = static_cast<int>(clamped.g * 255);
    int int_b = static_cast<int>(clamped.b * 255);
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

bool Color::isBlack() const {
    return r == 0 && g == 0 && b == 0;
}

Color Color::createGrey(float grey) {
    return {grey, grey, grey};
}

Color Color::createBlack() {
    return {};
}

Color Color::createWhite() {
    return {1, 1, 1};
}

Color Color::fromRGB(int r, int g, int b) {
    return {static_cast<float>(r) / 255.f, static_cast<float>(g) / 255.f, static_cast<float>(b) / 255.f};
}

Color Color::createRandom() {
    return {Random::random(), Random::random(), Random::random()};
}

} // namespace crayg