#pragma once
#include "FilmBufferBase.h"
#include "ValueTrait.h"
#include "basics/Color.h"
#include "basics/Vector2.h"
#include "utils/Preconditions.h"
#include <cstdint>

namespace crayg {

template <typename T, int channelCount> struct ValueBuffer : public FilmBufferBase<T, channelCount> {

    ValueBuffer(int width, int height) : FilmBufferBase<T, channelCount>(width, height) {
    }

    explicit ValueBuffer(const Resolution &resolution) : FilmBufferBase<T, channelCount>(resolution) {
    }

    void write(const Vector2i &pixelPosition, float value) {
        CRAYG_CHECKD_IS_VALID_INDEX((FilmBufferBase<T, channelCount>::index(pixelPosition)),
                                    (FilmBufferBase<T, channelCount>::pixelCount()));
        const int index = FilmBufferBase<T, channelCount>::index(pixelPosition);
        FilmBufferBase<T, channelCount>::data[index].value[0] = ValueTrait<T>::fromFloat(value);
    }

    void write(const Vector2i &pixelPosition, const Color &value) {
        CRAYG_CHECKD_IS_VALID_INDEX((FilmBufferBase<T, channelCount>::index(pixelPosition)),
                                    (FilmBufferBase<T, channelCount>::pixelCount()));
        for (int i = 0; i < channelCount; i++) {
            const int index = FilmBufferBase<T, channelCount>::index(pixelPosition);
            FilmBufferBase<T, channelCount>::data[index].value[i] = ValueTrait<T>::fromFloat(value.data()[i]);
        }
    }
};

typedef ValueBuffer<float, 1> FloatValueBuffer;
typedef ValueBuffer<uint8_t, 1> IntValueBuffer;
typedef ValueBuffer<float, 3> Color3fValueBuffer;
typedef ValueBuffer<uint8_t, 3> Color3iValueBuffer;

#define EnumerateAllValueBuffers FloatValueBuffer, IntValueBuffer, Color3fValueBuffer, Color3iValueBuffer
#define EnumerateAllValueBufferPtrs FloatValueBuffer *, IntValueBuffer *, Color3fValueBuffer *, Color3iValueBuffer *

typedef std::variant<EnumerateAllValueBuffers> ValueBufferVariant;
typedef std::variant<EnumerateAllValueBufferPtrs> ValueBufferVariantPtr;

}
