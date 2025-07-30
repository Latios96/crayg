#pragma once
#include "IntegratorSettingsValue.h"

#include <fmt/ostream.h>
#include <ostream>
#include <unordered_map>

namespace crayg {

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

template <> struct fmt::formatter<crayg::IntegratorSettings> : ostream_formatter {};
