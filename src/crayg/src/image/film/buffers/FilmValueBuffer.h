#pragma once
#include "FilmBufferBase.h"
#include "FilmValueTrait.h"
#include "crayg/foundation/assertions/Preconditions.h"
#include "crayg/foundation/math/geometry/Color.h"
#include "crayg/foundation/math/geometry/Vector2.h"
#include <cstdint>

namespace crayg {

template <typename T, int channelCount> struct FilmValueBuffer : public FilmBufferBase<T, channelCount> {

    FilmValueBuffer(int width, int height) : FilmBufferBase<T, channelCount>(width, height) {
    }

    explicit FilmValueBuffer(const Resolution &resolution) : FilmBufferBase<T, channelCount>(resolution) {
    }

    void write(const Vector2i &pixelPosition, float value) {
        CRAYG_CHECKD_IS_VALID_INDEX((FilmBufferBase<T, channelCount>::index(pixelPosition)),
                                    (FilmBufferBase<T, channelCount>::pixelCount()));
        const int index = FilmBufferBase<T, channelCount>::index(pixelPosition);
        FilmBufferBase<T, channelCount>::data[index].value[0] = FilmValueTrait<T>::fromFloat(value);
    }

    void write(const Vector2i &pixelPosition, const Color &value) {
        CRAYG_CHECKD_IS_VALID_INDEX((FilmBufferBase<T, channelCount>::index(pixelPosition)),
                                    (FilmBufferBase<T, channelCount>::pixelCount()));
        for (int i = 0; i < channelCount; i++) {
            const int index = FilmBufferBase<T, channelCount>::index(pixelPosition);
            FilmBufferBase<T, channelCount>::data[index].value[i] = FilmValueTrait<T>::fromFloat(value.data()[i]);
        }
    }
};

typedef FilmValueBuffer<float, 1> FloatValueBuffer;
typedef FilmValueBuffer<uint8_t, 1> IntValueBuffer;
typedef FilmValueBuffer<float, 3> Color3fValueBuffer;
typedef FilmValueBuffer<uint8_t, 3> Color3iValueBuffer;

#define EnumerateAllValueBuffers FloatValueBuffer, IntValueBuffer, Color3fValueBuffer, Color3iValueBuffer
#define EnumerateAllValueBufferPtrs FloatValueBuffer *, IntValueBuffer *, Color3fValueBuffer *, Color3iValueBuffer *

typedef std::variant<EnumerateAllValueBuffers> ValueBufferVariant;
typedef std::variant<EnumerateAllValueBufferPtrs> ValueBufferVariantPtr;

}
