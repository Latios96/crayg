#pragma once
#include <fmt/ostream.h>
#include <fmt/std.h>
#include <ostream>
#include <unordered_map>
#include <variant>

namespace crayg {

typedef std::variant<std::string, int, float> IntegratorSettingsValue;

class IntegratorSettings {
  public:
    explicit IntegratorSettings();
    explicit IntegratorSettings(const std::unordered_map<std::string, std::variant<std::string, int, float>> &settings);
    IntegratorSettingsValue getOrDefault(const std::string &name, const IntegratorSettingsValue &defaultValue) const;
    bool operator==(const IntegratorSettings &rhs) const;
    bool operator!=(const IntegratorSettings &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const IntegratorSettings &settings);

    std::unordered_map<std::string, std::variant<std::string, int, float>> settings;
};

} // crayg

template <> struct fmt::formatter<crayg::IntegratorSettings> : ostream_formatter {};
