#pragma once
#include <fmt/ostream.h>
#include <ostream>
#include <variant>

namespace crayg {

typedef std::variant<std::string, int, float> _IntegratorSettingsValue;

struct IntegratorSettingsValue : _IntegratorSettingsValue {

    IntegratorSettingsValue() = default;

    IntegratorSettingsValue(const char *value) : _IntegratorSettingsValue(value) {
    }

    IntegratorSettingsValue(const std::string &value) : _IntegratorSettingsValue(value) {
    }

    IntegratorSettingsValue(float value) : _IntegratorSettingsValue(value) {
    }

    IntegratorSettingsValue(int value) : _IntegratorSettingsValue(value) {
    }

    friend std::ostream &operator<<(std::ostream &os, const IntegratorSettingsValue &value) {
        std::visit([&os](auto v) { os << fmt::format("{}", v); }, value);
        return os;
    }
};

}

template <> struct fmt::formatter<crayg::IntegratorSettingsValue> : ostream_formatter {};
