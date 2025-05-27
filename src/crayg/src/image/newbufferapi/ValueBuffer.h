#pragma once
#include "BufferBase.h"
#include "ValueTrait.h"
#include "basics/Color.h"
#include "basics/Vector2.h"
#include <cstdint>

namespace crayg {

template <typename T, int channelCount> struct ValueBuffer : public BufferBase<T, channelCount> {

    ValueBuffer(int width, int height) : BufferBase<T, channelCount>(width, height) {
    }

    explicit ValueBuffer(const Resolution &resolution) : BufferBase<T, channelCount>(resolution) {
    }

    void write(const Vector2i &pixelPosition, float value) {
        const int index = BufferBase<T, channelCount>::index(pixelPosition);
        BufferBase<T, channelCount>::data[index].value[0] = ValueTrait<T>::fromFloat(value);
    }

    void write(const Vector2i &pixelPosition, const Color &value) {
        for (int i = 0; i < channelCount; i++) {
            const int index = BufferBase<T, channelCount>::index(pixelPosition);
            BufferBase<T, channelCount>::data[index].value[i] = ValueTrait<T>::fromFloat(value.data()[i]);
        }
    }
};

typedef ValueBuffer<float, 1> FloatValueBuffer;
typedef ValueBuffer<uint8_t, 1> IntValueBuffer;
typedef ValueBuffer<float, 3> Color3fValueBuffer;
typedef ValueBuffer<uint8_t, 3> Color3iValueBuffer;
typedef std::variant<FloatValueBuffer, IntValueBuffer, Color3fValueBuffer, Color3iValueBuffer> ValueBufferVariant;

}
