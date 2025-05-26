#pragma once
#include "ValueTrait.h"
#include "basics/Color.h"
#include "basics/Vector2.h"
#include <fmt/format.h>
#include <string>

namespace crayg {

template <typename T, int channelCount> struct BufferBase {
    // todo static_assert that channelCount is 1 or 3
    BufferBase() = default;

    BufferBase(int width, int height) : width(width), height(height) {
        values = new T[valueCount()](); // todo make sure this is zero initialized
    }

    struct PixelValue {
        T value[channelCount];
    };

    PixelValue *values = nullptr;
    int width = 0;
    int height = 0;

    float getFloat(const Vector2i &pixelPosition) const { // todo test
        // return the value of the first channel
    }

    Color getColor(const Vector2i &pixelPosition) const { // todo test
        // return the value of the first channel if only one else return all three
    }

    int pixelCount() const { // todo test
        return width * height;
    }

    std::string describe() const { // todo test
        return fmt::format("{}, {}bit", ValueTrait<T>::name, sizeof(T) * 8);
    }

    // todo operators like equal and ostream

    virtual ~BufferBase() {
        delete[] values;
    }
};

}
