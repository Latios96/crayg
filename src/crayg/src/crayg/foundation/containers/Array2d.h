#pragma once
#include "crayg/foundation/assertions/Preconditions.h"
#include "crayg/foundation/exceptions/Exceptions.h"
#include "crayg/foundation/math/geometry/Vector2.h"
#include "crayg/foundation/math/geometry/Vector2_formatter.h"
#include <vector>

#include <cstddef>

namespace crayg {

template <typename T> class Array2d {
  public:
    Array2d() = default;

    Array2d(size_t width, size_t height) : width(width), height(height) {
        storage = std::vector<T>(width * height);
    }

    Array2d(size_t width, size_t height, std::initializer_list<T> initializer) : width(width), height(height) {
        CRAYG_CHECK_EQUALS(width * height, initializer.size());
        storage = initializer;
    }

    Array2d(size_t width, size_t height, float *data) : width(width), height(height) {
        storage = std::vector<T>(width * height);
        for (size_t i = 0; i < storage.size(); i++) {
            storage[i] = data[i];
        }
    }

    T &operator[](const Vector2i &i) {
        CRAYG_CHECKD_IS_VALID_INDEX(index(i.x, i.y), size());
        return storage[index(i.x, i.y)];
    }

    const T &operator[](const Vector2i &i) const {
        CRAYG_CHECKD_IS_VALID_INDEX(index(i.x, i.y), size());
        return storage[index(i.x, i.y)];
    }

    size_t index(size_t xIndex, size_t yIndex) const {
        return xIndex + width * yIndex;
    }

    friend bool operator==(const Array2d &lhs, const Array2d &rhs) {
        return lhs.storage == rhs.storage && lhs.width == rhs.width && lhs.height == rhs.height;
    }

    friend bool operator!=(const Array2d &lhs, const Array2d &rhs) {
        return !(lhs == rhs);
    }

    T *data() {
        return storage.data();
    }

    size_t size() const {
        return width * height;
    }

    auto begin() {
        return storage.begin();
    }

    auto end() {
        return storage.end();
    }

    auto begin() const {
        return storage.begin();
    }

    auto end() const {
        return storage.end();
    }

    auto front() {
        return storage.front();
    }

    auto back() {
        return storage.back();
    }

    auto front() const {
        return storage.front();
    }

    auto back() const {
        return storage.back();
    }

  private:
    std::vector<T> storage;
    size_t width = 0;
    size_t height = 0;
};

}