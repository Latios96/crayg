#pragma once
#include <optional>
#include <vector>

namespace crayg {

template <typename Left, typename Right> struct ValueMapper {
    ValueMapper(const std::vector<std::pair<Left, Right>> &values) : values(values) {
    }

    std::optional<Right> mapFromLeft(const Left &left) {
        for (auto &pair : values) {
            if (pair.first == left) {
                return pair.second;
            }
        }
        return std::nullopt;
    }

    std::optional<Left> mapFromRight(const Right &right) {
        for (auto &pair : values) {
            if (pair.second == right) {
                return pair.first;
            }
        }
        return std::nullopt;
    }

    std::vector<std::pair<Left, Right>> values;
};

}