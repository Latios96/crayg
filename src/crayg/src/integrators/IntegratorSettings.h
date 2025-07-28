#pragma once
#include <fmt/ostream.h>
#include <ostream>
#include <unordered_map>
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

class IntegratorSettings {
  public:
    explicit IntegratorSettings();
    explicit IntegratorSettings(const std::unordered_map<std::string, IntegratorSettingsValue> &settings);
    IntegratorSettingsValue getOrDefault(const std::string &name, const IntegratorSettingsValue &defaultValue) const;
    bool operator==(const IntegratorSettings &rhs) const;
    bool operator!=(const IntegratorSettings &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const IntegratorSettings &settings);

    std::unordered_map<std::string, IntegratorSettingsValue> settings;
};

}

template <> struct fmt::formatter<crayg::IntegratorSettingsValue> : ostream_formatter {};

template <> struct fmt::formatter<crayg::IntegratorSettings> : ostream_formatter {};
