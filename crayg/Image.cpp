//
// Created by jan on 15.08.18.
//

#include "Image.h"

Image::Image(int width, int height)  {
    this->width = width;
    this->height = height;

    int size = width * height * 3;
    values = new float[size];

    for(int i=0; i<size;i++){
        values[i] = 0;
    }
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

void Image::setValue(int x, int y, const Vector3f &color){
    int index = this->index(x,y);
    values[index] = color.x;
    values[index +1 ] = color.y;
    values[index + 2] = color.z;
}

void Image::setValue(int x, int y, float r, float g, float b) {
    int index = this->index(x,y);
    values[index] = r;
    values[index +1 ] = g;
    values[index + 2] = b;
}

Vector3f Image::getValue(int x, int y) const {
    int index = this->index(x,y);
    return {values[index], values[index+1], values[index+2]};
}
