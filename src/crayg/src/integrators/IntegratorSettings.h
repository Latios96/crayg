#ifndef CRAYG_SRC_CRAYG_SRC_INTEGRATORS_INTEGRATORSETTINGS_H_
#define CRAYG_SRC_CRAYG_SRC_INTEGRATORS_INTEGRATORSETTINGS_H_
#include <fmt/ostream.h>
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

template <> struct fmt::formatter<crayg::IntegratorSettingsValue> {
    template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template <typename FormatContext> auto format(crayg::IntegratorSettingsValue const &value, FormatContext &ctx) {
        return std::visit([&ctx](auto &v) { return fmt::format_to(ctx.out(), fmt::format("{}", v)); }, value);
    };
};

#endif // CRAYG_SRC_CRAYG_SRC_INTEGRATORS_INTEGRATORSETTINGS_H_
