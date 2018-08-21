//
// Created by jan on 21.08.18.
//

#ifndef CRAYG_COLOR_H
#define CRAYG_COLOR_H

#include <ostream>

// todo what about alpha?
class Color {
public:
    float r,g,b;

    /**
     * Creates a new Color instance and defaults to Black (0,0,0)
     */
    Color();

    /**
     * Creates a new Color instance and sets color components to given parameters
     * @param r
     * @param g
     * @param b
     */
    Color(float r, float g, float b);

    /**
     * Adds the two colors component-wise, r+r, g+g, b+b
     * @param otherColor
     * @return
     */
    Color operator+(const Color &otherColor);
    /**
     * Subtracts the two colors component-wise, r-r, g-g, b-b
     * @param otherColor
     * @return
     */
    Color operator-(const Color &otherColor);
    /**
     * Multiplies the two colors component-wise, r*r, g*g, b*b
     * @param otherColor
     * @return
     */
    Color operator*(const Color &otherColor);

    /**
     * Multiplies every Component with the given scalar and returns a new color value.
     * @param otherColor
     * @return
     */
    Color operator*(float scalar);
    /**
     * Clamps the color components to 1
     * @return
     */
    Color clamp();
    /**
     * Returns the color components as int between 0-255. If float components are larger than 1, they are clamped.
     * @return
     */
    std::tuple<int, int, int> getRgbValues();

    friend std::ostream &operator<<(std::ostream &os, const Color &color);

};


#endif //CRAYG_COLOR_H
