#ifndef CRAYG_COLOR_H
#define CRAYG_COLOR_H

#include <ostream>
#include <tuple>

namespace crayg {

class Color {
  public:
    float r, g, b;

    Color();

    Color(float r, float g, float b);

    static Color createGrey(float grey);
    static Color createBlack();
    static Color createWhite();

    static Color fromRGB(int r, int g, int b);

    static Color createRandom();

    Color operator+(const Color &otherColor) const;

    Color operator+(float value) const;

    Color operator-(const Color &otherColor) const;

    Color operator*(const Color &otherColor) const;

    Color operator*(float scalar) const;

    Color operator/(float scalar) const;

    bool operator==(const Color &color) const;

    bool operator!=(const Color &color) const;

    bool operator<(const Color &rhs) const;
    bool operator>(const Color &rhs) const;
    bool operator<=(const Color &rhs) const;
    bool operator>=(const Color &rhs) const;

    Color clamp() const;

    bool isBlack() const;

    std::tuple<int, int, int> getRgbValues() const;

    Color pow(float exponent) const;

    friend std::ostream &operator<<(std::ostream &os, const Color &color);
};

} // namespace crayg
#endif // CRAYG_COLOR_H
