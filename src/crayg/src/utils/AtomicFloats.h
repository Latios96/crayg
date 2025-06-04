#pragma once
#include "BitCast.h"
#include <atomic>

namespace crayg {

template <typename FloatingPointType, typename StorageType> struct AtomicRefFloatingPoint {
    explicit AtomicRefFloatingPoint(FloatingPointType &ref) : bits((StorageType &)ref) {
    }

    FloatingPointType get() const {
        return BitCast::floatingFromBits<FloatingPointType, StorageType>(bits);
    }

    void atomicAdd(FloatingPointType x) {
        StorageType old_bits = bits.load();
        StorageType new_bits;
        do {
            double old_val = BitCast::floatingFromBits<FloatingPointType, StorageType>(old_bits);
            double new_val = old_val + x;
            new_bits = BitCast::floatingToBits<FloatingPointType, StorageType>(new_val);
        } while (!bits.compare_exchange_weak(old_bits, new_bits));
    }

  private:
    std::atomic_ref<StorageType> bits;
};

template <typename FloatingPointType, typename StorageType> struct AtomicFloatingPoint {
    AtomicFloatingPoint() = default;

    FloatingPointType get() const {
        return BitCast::floatingFromBits<FloatingPointType, StorageType>(bits);
    }

    void atomicAdd(FloatingPointType x) {
        StorageType old_bits = bits.load();
        StorageType new_bits;
        do {
            double old_val = BitCast::floatingFromBits<FloatingPointType, StorageType>(old_bits);
            double new_val = old_val + x;
#ifdef CRAYG_DEBUG_BUILD
            value = new_val;
#endif
            new_bits = BitCast::floatingToBits<FloatingPointType, StorageType>(new_val);
        } while (!bits.compare_exchange_weak(old_bits, new_bits));
    }

  private:
    std::atomic<StorageType> bits = 0;
#ifdef CRAYG_DEBUG_BUILD
    double value = 0;
#endif
};

typedef AtomicRefFloatingPoint<float, uint32_t> AtomicFloatRef;
typedef AtomicRefFloatingPoint<double, uint64_t> AtomicDoubleRef;
typedef AtomicFloatingPoint<float, uint32_t> AtomicFloat;
typedef AtomicFloatingPoint<double, uint64_t> AtomicDouble;

}
