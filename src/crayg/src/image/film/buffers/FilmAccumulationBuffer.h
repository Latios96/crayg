#pragma once
#include "FilmBufferBase.h"
#include "basics/Color.h"
#include "basics/Vector2.h"
#include "crayg/foundation/assertions/Preconditions.h"
#include "crayg/foundation/exceptions/Exceptions.h"
#include "crayg/foundation/math/geometry/Tile.h"
#include "crayg/foundation/numerics/AtomicFloats.h"

namespace crayg {

template <typename T, int channelCount> struct FilmAccumulationBuffer : public FilmBufferBase<T, channelCount> {
    static_assert(std::is_floating_point_v<T>);

    FilmAccumulationBuffer(int width, int height) : FilmBufferBase<T, channelCount>(width, height) {
        sum = new SumType[FilmBufferBase<T, channelCount>::pixelCount()]();
        CRAYG_CHECK_NOT_NULLPTR(sum);
        weight = new AtomicDouble[FilmBufferBase<T, channelCount>::pixelCount()]();
        CRAYG_CHECK_NOT_NULLPTR(weight);
    }

    explicit FilmAccumulationBuffer(const Resolution &resolution) : FilmBufferBase<T, channelCount>(resolution) {
        sum = new SumType[FilmBufferBase<T, channelCount>::pixelCount()]();
        CRAYG_CHECK_NOT_NULLPTR(sum);
        weight = new AtomicDouble[FilmBufferBase<T, channelCount>::pixelCount()]();
        CRAYG_CHECK_NOT_NULLPTR(weight);
    }

    FilmAccumulationBuffer(const FilmAccumulationBuffer &other) : FilmBufferBase<T, channelCount>(other) {
        sum = new SumType[FilmBufferBase<T, channelCount>::pixelCount()]();
        CRAYG_CHECK_NOT_NULLPTR(sum);
        memcpy(other.sum, sum, FilmBufferBase<T, channelCount>::pixelCount() * sizeof(SumType));
        weight = new AtomicDouble[FilmBufferBase<T, channelCount>::pixelCount()]();
        CRAYG_CHECK_NOT_NULLPTR(weight);
        memcpy(other.weight, weight, FilmBufferBase<T, channelCount>::pixelCount() * sizeof(AtomicDouble));
    }

    FilmAccumulationBuffer &operator=(const FilmAccumulationBuffer &other) {
        if (this == &other) {
            return *this;
        }
        FilmBufferBase<T, channelCount>::operator=(other);
        sum = new SumType[FilmBufferBase<T, channelCount>::pixelCount()]();
        CRAYG_CHECK_NOT_NULLPTR(sum);
        memcpy(other.sum, sum, FilmBufferBase<T, channelCount>::pixelCount() * sizeof(SumType));
        weight = new AtomicDouble[FilmBufferBase<T, channelCount>::pixelCount()]();
        CRAYG_CHECK_NOT_NULLPTR(weight);
        memcpy(other.weight, weight, FilmBufferBase<T, channelCount>::pixelCount() * sizeof(AtomicDouble));
        return *this;
    }

    void add(const Vector2i &pixelPosition, float value) {
        const auto index = FilmBufferBase<T, channelCount>::index(pixelPosition);
        CRAYG_CHECKD_IS_VALID_INDEX((FilmBufferBase<T, channelCount>::index(pixelPosition)),
                                    (FilmBufferBase<T, channelCount>::pixelCount()));

        for (int i = 0; i < channelCount; i++) {
            sum[index].value[i].atomicAdd(value);
        }
        weight[index].atomicAdd(1);
    }

    void add(const Vector2i &pixelPosition, const Color &value) {
        const auto index = FilmBufferBase<T, channelCount>::index(pixelPosition);
        CRAYG_CHECKD_IS_VALID_INDEX((FilmBufferBase<T, channelCount>::index(pixelPosition)),
                                    (FilmBufferBase<T, channelCount>::pixelCount()));

        for (int i = 0; i < channelCount; i++) {
            sum[index].value[i].atomicAdd(value.data()[i]);
        }
        weight[index].atomicAdd(1);
    }

    void updateAverages() {
        for (int i = 0; i < FilmBufferBase<T, channelCount>::pixelCount(); i++) {
            updateAverage(i);
        }
    }

    void updateAveragesInTile(const Tile &tile) {
        for (int tileY = 0; tileY < tile.getHeight(); tileY++) {
            for (int tileX = 0; tileX < tile.getWidth(); tileX++) {
                const Vector2i globalPosition = tile.getPosition() + Vector2i(tileX, tileY);
                updateAverage(FilmBufferBase<T, channelCount>::index(globalPosition));
            }
        }
    }

    void updateAverage(int index) {
        double w = weight[index].get();
        if (w != 0) {
            for (int c = 0; c < channelCount; c++) {
                FilmBufferBase<T, channelCount>::data[index].value[c] = sum[index].value[c].get() / w;
            }
        }
    }

    bool sumIsConstant(const double &constantSum) const {
        for (int i = 0; i < FilmBufferBase<T, channelCount>::pixelCount(); i++) {
            if (sum[i].value[0].get() != constantSum) {
                return false;
            }
        }
        return true;
    }

    bool sumIsConstant(const Color &color) const {
        for (int i = 0; i < FilmBufferBase<T, channelCount>::pixelCount(); i++) {
            for (int c = 0; c < channelCount; c++) {
                if (sum[i].value[c].get() != color.data()[c]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool sumIsZero() const {
        return sumIsConstant(0);
    }

    bool weightIsConstant(const double &constantWeight) const {
        for (int i = 0; i < FilmBufferBase<T, channelCount>::pixelCount(); i++) {
            if (weight[i].get() != constantWeight) {
                return false;
            }
        }
        return true;
    }

    bool weightIsZero() const {
        return weightIsConstant(0);
    }

    double getWeight(const Vector2i &pixelPosition) const {
        const int i = FilmBufferBase<T, channelCount>::index(pixelPosition);
        const int size = FilmBufferBase<T, channelCount>::width * FilmBufferBase<T, channelCount>::height;
        CRAYG_CHECKD_IS_VALID_INDEX(i, size);

        return weight[i].get();
    }

    struct SumType {
        AtomicDouble value[channelCount];
    };

    // todo use Array2D
    SumType *sum;
    AtomicDouble *weight;
};

typedef FilmAccumulationBuffer<float, 1> FloatAccumulationBuffer;
typedef FilmAccumulationBuffer<float, 3> Color3fAccumulationBuffer;

#define EnumerateAllAccumulationBuffers FloatAccumulationBuffer, Color3fAccumulationBuffer
#define EnumerateAllAccumulationBufferPtrs FloatAccumulationBuffer *, Color3fAccumulationBuffer *

typedef std::variant<EnumerateAllAccumulationBuffers> AccumulationBufferVariant;
typedef std::variant<EnumerateAllAccumulationBufferPtrs> AccumulationBufferVariantPtr;

}
