#pragma once
#include "ValueTrait.h"
#include "basics/Color.h"
#include "basics/Resolution.h"
#include "basics/Vector2.h"
#include "utils/Preconditions.h"

#include <fmt/format.h>
#include <string>
#include <variant>

// todo what is better naming for all of this? PixelBuffer? RenderBuffer?

namespace crayg {

template <typename T, int channelCount> struct BufferBase {
    static_assert(channelCount == 1 || channelCount == 3);

    BufferBase(int width, int height) : width(width), height(height) {
        data = new PixelValue[pixelCount()]();
        CRAYG_CHECK_NOT_NULLPTR(data);
    }

    explicit BufferBase(const Resolution &resolution) : width(resolution.getWidth()), height(resolution.getHeight()) {
        data = new PixelValue[pixelCount()]();
        CRAYG_CHECK_NOT_NULLPTR(data);
    }

    BufferBase(const BufferBase &other) : width(other.width), height(other.height) {
        data = new PixelValue[pixelCount()]();
        CRAYG_CHECK_NOT_NULLPTR(data);
        memcpy(data, other.data, pixelCount() * sizeof(PixelValue));
    }

    BufferBase(BufferBase &&other) noexcept : data(other.data), width(other.width), height(other.height) {
        other.data = nullptr;
    }

    BufferBase &operator=(const BufferBase &other) {
        if (this == &other) {
            return *this;
        }
        width = other.width;
        height = other.height;
        memcpy(data, other.data, pixelCount() * sizeof(PixelValue));
        return *this;
    }

    BufferBase &operator=(BufferBase &&other) noexcept {
        if (this == &other) {
            return *this;
        }
        width = other.width;
        height = other.height;
        memcpy(data, other.data, pixelCount() * sizeof(PixelValue));
        return *this;
    }

    float getFloat(const Vector2i &pixelPosition) const {
        CRAYG_CHECKD_IS_VALID_INDEX(index(pixelPosition), width * height);

        return ValueTrait<T>::toFloat(data[index(pixelPosition)].value[0]);
    }

    Color getColor(const Vector2i &pixelPosition) const {
        CRAYG_CHECKD_IS_VALID_INDEX(index(pixelPosition), width * height);
        Color color;
        for (int i = 0; i < channelCount; i++) {
            color.data()[i] = ValueTrait<T>::toFloat(data[index(pixelPosition)].value[i]);
        }
        return color;
    }

    bool isWhite() const {
        return isColor(Color::createWhite());
    }

    bool isBlack() const {
        return isColor(Color::createBlack());
    }

    bool isColor(const Color &color) const {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (getColor({x, y}) != color) {
                    return false;
                }
            }
        }
        return true;
    }

    int pixelCount() const {
        return width * height;
    }

    std::string describe() const {
        return fmt::format("{}x {}", channelCount, ValueTrait<T>::name);
    }

    friend std::ostream &operator<<(std::ostream &os, const BufferBase<T, channelCount> &buffer) {
        os << ToStringHelper("PixelBuffer")
                  .addMember("width", buffer.width)
                  .addMember("height", buffer.height)
                  .addMember("format", fmt::format(R"('{}')", describe()))
                  .finish();
        return os;
    }

    virtual ~BufferBase() {
        delete[] data;
    }

    struct PixelValue {
        T value[channelCount];
    };

    // todo use an Array2d instead
    // todo rename to color? pixel? pixelValue? find better name than "data"
    PixelValue *data = nullptr;
    int width = 0;
    int height = 0;
    const int chCount = channelCount;

    int index(const Vector2i &pixelPosition) const {
        return (pixelPosition.x + width * pixelPosition.y);
    }
};

typedef BufferBase<float, 1> FloatBufferBase;
typedef BufferBase<uint8_t, 1> IntBufferBase;
typedef BufferBase<float, 3> Color3fBufferBase;
typedef BufferBase<uint8_t, 3> Color3iBufferBase;
typedef std::variant<FloatBufferBase, IntBufferBase, Color3fBufferBase, Color3iBufferBase> BufferBaseVariant;

}
