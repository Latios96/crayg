//
// Created by jan on 15.08.18.
//

#ifndef CRAYG_IMAGE_H
#define CRAYG_IMAGE_H


#include "Vector3f.h"

class Image {

private:
    int width, height;
    float *values;

    /**
     * Computes the index in the 1D-array from x and y.
     * @param x x coordinate
     * @param y x coordinate
     * @return index in the 1d array
     */
    int index(int x, int y) const {
        return (x + width * y)*3;
    }

public:
    /**
     * Creates a new Image of given dimensions. All Pixel values are initialized to 0.
     * @param width width of the new image
     * @param height height of the new image
     */
    Image(int width, int height);

    int get_width() const;

    int get_height() const;

    void set_value(int x, int y, const Vector3f &color);

    void set_value(int x, int y, float r, float g, float b);

    Vector3f get_value(int x, int y) const;

    ~Image() {
        delete[] values;
    }

};


#endif //CRAYG_IMAGE_H
