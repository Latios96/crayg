#pragma once
#include "FilmBufferBase.h"
#include "FilmValueTrait.h"
#include "crayg/foundation/assertions/Preconditions.h"
#include "crayg/foundation/math/geometry/Color.h"
#include "crayg/foundation/math/geometry/Vector2.h"
#include "crayg/foundation/numerics/AtomicFloats.h"
#include <atomic>
#include <cstdint>

namespace crayg {

template <typename T> struct AtomicRefTrait {
    static void add(float &value, float &valueToAdd);
};

template <> struct AtomicRefTrait<float> {
    static void add(float &value, float &valueToAdd) {
        AtomicFloatRef atomicRef(value);
        atomicRef.atomicAdd(valueToAdd);
    }
};

template <> struct AtomicRefTrait<uint8_t> {
    static void add(uint8_t &value, uint8_t &valueToAdd) {
        std::atomic_ref<uint8_t> atomicRef(value);
        atomicRef.fetch_add(valueToAdd);
    }
};

template <typename T, int channelCount> struct FilmSumBuffer : public FilmBufferBase<T, channelCount> {

    FilmSumBuffer(int width, int height) : FilmBufferBase<T, channelCount>(width, height) {
    }

    explicit FilmSumBuffer(const Resolution &resolution) : FilmBufferBase<T, channelCount>(resolution) {
    }

    void add(const Vector2i &pixelPosition, float value) {
        CRAYG_CHECKD_IS_VALID_INDEX((FilmBufferBase<T, channelCount>::index(pixelPosition)),
                                    (FilmBufferBase<T, channelCount>::pixelCount()));
        const int index = FilmBufferBase<T, channelCount>::index(pixelPosition);
        T v = FilmValueTrait<T>::fromFloat(value);
        AtomicRefTrait<T>::add(FilmBufferBase<T, channelCount>::data[index].value[0], v);
    }

    void add(const Vector2i &pixelPosition, const Color &value) {
        CRAYG_CHECKD_IS_VALID_INDEX((FilmBufferBase<T, channelCount>::index(pixelPosition)),
                                    (FilmBufferBase<T, channelCount>::pixelCount()));
        for (int i = 0; i < channelCount; i++) {
            const int index = FilmBufferBase<T, channelCount>::index(pixelPosition);
            T v = FilmValueTrait<T>::fromFloat(value.data()[i]);
            AtomicRefTrait<T>::add(FilmBufferBase<T, channelCount>::data[index].value[i], v);
        }
    }
};

typedef FilmSumBuffer<float, 1> FloatSumBuffer;
typedef FilmSumBuffer<uint8_t, 1> IntSumBuffer;
typedef FilmSumBuffer<float, 3> Color3fSumBuffer;
typedef FilmSumBuffer<uint8_t, 3> Color3iSumBuffer;

#define EnumerateAllSumBuffers FloatSumBuffer, IntSumBuffer, Color3fSumBuffer, Color3iSumBuffer
#define EnumerateAllSumBufferPtrs FloatSumBuffer *, IntSumBuffer *, Color3fSumBuffer *, Color3iSumBuffer *

typedef std::variant<EnumerateAllSumBuffers> SumBufferVariant;
typedef std::variant<EnumerateAllSumBufferPtrs> SumBufferVariantPtr;

}
