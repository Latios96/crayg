#pragma once

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <ostream>
#include <tbb/parallel_for.h>

namespace crayg {

struct Index2d {
    int x, y;

    Index2d() = default;

    Index2d(int x, int y) : x(x), y(y) {
    }

    friend bool operator==(const Index2d &lhs, const Index2d &rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    friend bool operator!=(const Index2d &lhs, const Index2d &rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const Index2d &lhs, const Index2d &rhs) {
        if (lhs.x < rhs.x) {
            return true;
        }
        if (rhs.x < lhs.x) {
            return false;
        }
        return lhs.y < rhs.y;
    }

    friend bool operator<=(const Index2d &lhs, const Index2d &rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>(const Index2d &lhs, const Index2d &rhs) {
        return rhs < lhs;
    }

    friend bool operator>=(const Index2d &lhs, const Index2d &rhs) {
        return !(lhs < rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const Index2d &obj) {
        return os << fmt::format("({},{})", obj.x, obj.y);
    }
};

template <typename Func> void parallelFor2d(int width, int height, Func &&func) {
    tbb::parallel_for(0, width * height, [width, &func](int i) {
        const Index2d index2d = Index2d(i % width, i / width);
        func(index2d);
    });
}

template <typename Func, typename Res> void parallelFor2d(const Res &res, Func &&func) {
    parallelFor2d(res.getWidth(), res.getHeight(), func);
}

}

template <> struct fmt::formatter<crayg::Index2d> : ostream_formatter {};
