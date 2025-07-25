#pragma once

#include <chrono>
#include <fmt/chrono.h>
#include <fmt/format.h>
#include <fmt/std.h>
#include <ostream>
#include <string>
#include <variant>

namespace crayg {

typedef std::variant<std::string, int, float, std::chrono::seconds> _ImageMetadataValue;

struct ImageMetadataValue : std::variant<std::string, int, float, std::chrono::seconds> {

    ImageMetadataValue() = default;

    ImageMetadataValue(const char *value) : _ImageMetadataValue(value) {
    }

    ImageMetadataValue(const std::string &value) : _ImageMetadataValue(value) {
    }

    ImageMetadataValue(int value) : _ImageMetadataValue(value) {
    }

    ImageMetadataValue(float value) : _ImageMetadataValue(value) {
    }

    ImageMetadataValue(std::chrono::seconds value) : _ImageMetadataValue(value) {
    }

    friend std::ostream &operator<<(std::ostream &os, const ImageMetadataValue &value) {
        std::visit([&os](auto v) { os << fmt::format("{}", v); }, value);
        return os;
    }
};

}

template <> struct fmt::formatter<crayg::ImageMetadataValue> : ostream_formatter {};
