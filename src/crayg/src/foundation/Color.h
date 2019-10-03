//
// Created by jan on 21.08.18.
//

#ifndef CRAYG_COLOR_H
#define CRAYG_COLOR_H

#include <ostream>

// todo what about alpha?
class Color {
 public:
    float r, g, b;

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

    static Color createGrey(float grey) {
        return {grey, grey, grey};
    }

    static Color createBlack() {
        return {};
    }
    static Color createWhite() {
        return {1, 1, 1};
    }

    /**
     * Adds the two colors component-wise, r+r, g+g, b+b
     * @param otherColor
     * @return
     */
    Color operator+(const Color &otherColor);
    /**
     * Adds the given float to all components of this color
     * @param value value to add to all components
     * @return new color with all components increased by value
     */
    Color operator+(float value);
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
     * Two colors are equal if their r,g,b components are equal
     * @param color 
     * @return 
     */
    bool operator==(const Color &color) const;

    bool operator!=(const Color &color) const;
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
