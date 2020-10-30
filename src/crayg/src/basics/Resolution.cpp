//
// Created by Jan on 30.10.2020.
//

#include <utils/ToStringHelper.h>
#include "Resolution.h"
Resolution::Resolution(int width, int height) : width(width), height(height) {}
bool Resolution::operator==(const Resolution &rhs) const {
    return width == rhs.width &&
        height == rhs.height;
}
bool Resolution::operator!=(const Resolution &rhs) const {
    return !(rhs == *this);
}
bool Resolution::operator<(const Resolution &rhs) const {
    if (width < rhs.width)
        return true;
    if (rhs.width < width)
        return false;
    return height < rhs.height;
}
bool Resolution::operator>(const Resolution &rhs) const {
    return rhs < *this;
}
bool Resolution::operator<=(const Resolution &rhs) const {
    return !(rhs < *this);
}
bool Resolution::operator>=(const Resolution &rhs) const {
    return !(*this < rhs);
}
std::ostream &operator<<(std::ostream &os, const Resolution &resolution) {
    os << ToStringHelper("Resolution")
        .addMember("width", resolution.width)
        .addMember("height", resolution.height)
        .finish();
    return os;
}
Resolution::Resolution() : width(0), height(0) {

}
const int Resolution::getWidth() const {
    return width;
}
const int Resolution::getHeight() const {
    return height;
}
Resolution::Resolution(const Resolution &resolution) : width(resolution.width), height(resolution.height) {

}
