#pragma once
#include "FilmValueTrait.h"
#include "crayg/foundation/assertions/Preconditions.h"
#include "crayg/foundation/exceptions/Exceptions.h"
#include "crayg/foundation/math/geometry/Color.h"
#include "crayg/foundation/math/geometry/Resolution.h"
#include "crayg/foundation/math/geometry/Vector2.h"
#include "crayg/image/PixelFormat.h"

#include <fmt/format.h>
#include <string>
#include <variant>

namespace crayg {

template <typename T, int channelCount> struct FilmBufferBase {
    static_assert(channelCount == 1 || channelCount == 3);

    FilmBufferBase(int width, int height) : width(width), height(height) {
        data = new PixelValue[pixelCount()]();
        CRAYG_CHECK_NOT_NULLPTR(data);
    }

    explicit FilmBufferBase(const Resolution &resolution)
        : width(resolution.getWidth()), height(resolution.getHeight()) {
        data = new PixelValue[pixelCount()]();
        CRAYG_CHECK_NOT_NULLPTR(data);
    }

    FilmBufferBase(const FilmBufferBase &other) : width(other.width), height(other.height) {
        data = new PixelValue[pixelCount()]();
        CRAYG_CHECK_NOT_NULLPTR(data);
        memcpy(data, other.data, pixelCount() * sizeof(PixelValue));
    }

    FilmBufferBase(FilmBufferBase &&other) noexcept : data(other.data), width(other.width), height(other.height) {
        other.data = nullptr;
    }

    FilmBufferBase &operator=(const FilmBufferBase &other) {
        if (this == &other) {
            return *this;
        }
        width = other.width;
        height = other.height;
        memcpy(data, other.data, pixelCount() * sizeof(PixelValue));
        return *this;
    }

    FilmBufferBase &operator=(FilmBufferBase &&other) noexcept {
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

        auto unknown = data[index(pixelPosition)].value[0];
        return FilmValueTrait<T>::toFloat(unknown);
    }

    Color getColor(const Vector2i &pixelPosition) const {
        CRAYG_CHECKD_IS_VALID_INDEX(index(pixelPosition), width * height);
        Color color;
        for (int i = 0; i < channelCount; i++) {
            color.data()[i] = FilmValueTrait<T>::toFloat(data[index(pixelPosition)].value[i]);
        }

        if (channelCount == 1) {
            color.g = color.r;
            color.b = color.r;
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
        return fmt::format("{}x {}", channelCount, FilmValueTrait<T>::name);
    }

    friend std::ostream &operator<<(std::ostream &os, const FilmBufferBase<T, channelCount> &buffer) {
        os << ToStringHelper("PixelBuffer")
                  .addMember("width", buffer.width)
                  .addMember("height", buffer.height)
                  .addMember("format", fmt::format(R"('{}')", buffer.describe()))
                  .finish();
        return os;
    }

    virtual ~FilmBufferBase() {
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
    const PixelFormat pixelFormat = FilmValueTrait<T>::pixelFormat;

    int index(const Vector2i &pixelPosition) const {
        return (pixelPosition.x + width * pixelPosition.y);
    }
};

typedef FilmBufferBase<float, 1> FloatBufferBase;
typedef FilmBufferBase<uint8_t, 1> IntBufferBase;
typedef FilmBufferBase<float, 3> Color3fBufferBase;
typedef FilmBufferBase<uint8_t, 3> Color3iBufferBase;
typedef std::variant<FloatBufferBase, IntBufferBase, Color3fBufferBase, Color3iBufferBase> BufferBaseVariant;

}
