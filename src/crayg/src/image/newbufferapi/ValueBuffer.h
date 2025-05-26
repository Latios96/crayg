#pragma once
#include "BufferBase.h"
#include "ValueTrait.h"
#include "basics/Color.h"
#include "basics/Vector2.h"
#include <cstdint>

namespace crayg {

template <typename T, int channelCount> struct ValueBuffer : BufferBase<T, channelCount> {

    void write(const Vector2i &pixelPosition, float value) { // todo test
        float fValue;
        ValueTrait<T>::fromFloat(value, &fValue);
        for (int i = 0; i < channelCount; i++) {
            BufferBase<T, channelCount>::values[i] = fValue;
        }
    }

    void write(const Vector2i &pixelPosition, const Color &value) { // todo test
        static_assert(channelCount == 1 || channelCount == 3);
        for (int i = 0; i < channelCount; i++) {
            ValueTrait<T>::fromFloat(value.data()[i], BufferBase<T, channelCount>::values[i]);
        }
    }
};

// todo test every single variant
typedef ValueBuffer<float, 1> FloatValueBuffer;
typedef ValueBuffer<uint8_t, 1> IntValueBuffer;
typedef ValueBuffer<float, 3> Color3fValueBuffer;
typedef ValueBuffer<uint8_t, 3> Color3iValueBuffer;

}
