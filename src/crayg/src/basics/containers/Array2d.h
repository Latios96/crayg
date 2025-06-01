#pragma once
#include "utils/Preconditions.h"
#include <vector>

#include <cstddef>

namespace crayg {

template <typename T> class Array2d {
  public:
    Array2d() = default;

    Array2d(size_t width, size_t height) : width(width), height(height) {
        storage.resize(size());
    }

    Array2d(Array2d<T> &&other) noexcept {
        storage = std::move(other.storage);
        height = other.height;
        width = other.width;
    }

    const T &get(size_t xIndex, size_t yIndex) const {
        CRAYG_CHECKD_IS_VALID_INDEX(index(xIndex, yIndex), size());
        return storage[index(xIndex, yIndex)];
    }

    T &get(size_t xIndex, size_t yIndex) {
        CRAYG_CHECKD_IS_VALID_INDEX(index(xIndex, yIndex), size());
        return storage[index(xIndex, yIndex)];
    }

    void set(size_t xIndex, size_t yIndex, const T &value) {
        CRAYG_CHECKD_IS_VALID_INDEX(index(xIndex, yIndex), size());
        storage[index(xIndex, yIndex)] = value;
    }

    size_t index(size_t xIndex, size_t yIndex) const {
        return xIndex + width * yIndex;
    }

    T *data() {
        return storage.data();
    }

    size_t size() {
        return width * height;
    }

    T *begin() {
        return storage.data();
    }

    T *end() {
        return storage.data() + size();
    }

  private:
    std::vector<T> storage;
    size_t width = 0;
    size_t height = 0;
};

}