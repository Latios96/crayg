#pragma once
#include "BufferBase.h"
#include "ValueTrait.h"
#include "basics/Color.h"
#include "basics/Vector2.h"
#include "image/ImageBucket.h"
#include <atomic>
#include <cstdint>

namespace crayg {

template <typename T, int channelCount> struct AccumulationBuffer : BufferBase<T, channelCount> {
    struct SumType {
        std::atomic<double> value[channelCount];
    };

    SumType *sum;
    std::atomic<double> *weight;

    void updateValues() {
        for (int i = 0; i < valueCount(); i++) { // todo test
            for (int c = 0; c < channelCount; c++) {
                BufferBase<T, channelCount>::values[i].value[c] = sum[i] / weight[i];
            }
        }
    }

    void updateValuesForBucket(const ImageBucket &imageBucket) { // todo test
        // update values for values in bucket
    }

    void add(const Vector2i &pixelPosition, float value) { // todo test
        float fValue;
        ValueTrait<T>::fromFloat(value, &fValue);
        for (int i = 0; i < channelCount; i++) {
            sum[i].fetch_add(fValue);
            weight[i].fetch_add(1);
        }
    }

    void add(const Vector2i &pixelPosition, const Color &value) { // todo test
        float fValue;
        ValueTrait<T>::fromFloat(value, &fValue);
        for (int i = 0; i < channelCount; i++) {
            sum[i].fetch_add(fValue);
            weight[i].fetch_add(1);
        }
    }
};

// todo test every single variant
typedef AccumulationBuffer<float, 1> FloatAccumulationBuffer;
typedef AccumulationBuffer<uint8_t, 1> IntAccumulationBuffer;
typedef AccumulationBuffer<float, 3> Color3fAccumulationBuffer;
typedef AccumulationBuffer<uint8_t, 3> Color3iAccumulationBuffer;

}
