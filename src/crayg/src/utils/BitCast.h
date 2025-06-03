#pragma once
#include <cstring>

namespace crayg {

struct BitCast {

    template <typename FloatingPointType, typename StorageType> static StorageType floatingToBits(FloatingPointType f) {
        static_assert(sizeof(FloatingPointType) == sizeof(StorageType));

        StorageType bitStorage;
        std::memcpy(&bitStorage, &f, sizeof(FloatingPointType));
        return bitStorage;
    }

    template <typename FloatingPointType, typename StorageType>
    static FloatingPointType floatingFromBits(StorageType bits) {
        static_assert(sizeof(FloatingPointType) == sizeof(StorageType));

        FloatingPointType f;
        std::memcpy(&f, &bits, sizeof(StorageType));
        return f;
    }
};

}
