//
// Created by jan on 21.08.18.
//

#include <tuple>
#include "Color.h"

std::ostream &operator<<(std::ostream &os, const Color &color) {
    os << "r: " << color.r << " g: " << color.g << " b: " << color.b;
    return os;
}

Color::Color() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

Color Color::operator+(const Color &otherColor) {
    return {r+otherColor.r, g+otherColor.g, b+otherColor.b};
}

Color Color::operator-(const Color &otherColor) {
    return {r-otherColor.r, g-otherColor.g, b-otherColor.b};
}

Color Color::operator*(const Color &otherColor) {
    return {r*otherColor.r, g*otherColor.g, b*otherColor.b};
}

Color Color::operator*(float scalar) {
    return {r*scalar, g*scalar, b*scalar};
}

Color Color::clamp() {
    return {std::min(1.0f,r), std::min(1.0f,g), std::min(1.0f,b)};
}

std::tuple<int, int, int> Color::getRgbValues() {
    int int_r = static_cast<int>(r * 255);
    int int_g = static_cast<int>(g * 255);
    int int_b = static_cast<int>(b * 255);
    return std::make_tuple(std::min(255,int_r), std::min(255,int_g), std::min(255,int_b));
}

bool Color::operator==(const Color &color) const {
    return (r== color.r && g== color.g && b== color.b);
}

bool Color::operator!=(const Color &color) const{
    return !(r== color.r && g== color.g && b== color.b);
}

