#ifndef CRAYG_SRC_CRAYG_SRC_INTEGRATORS_INTEGRATORSETTINGS_H_
#define CRAYG_SRC_CRAYG_SRC_INTEGRATORS_INTEGRATORSETTINGS_H_
#include <variant>
#include <unordered_map>
#include <ostream>

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
 private:
    std::unordered_map<std::string, std::variant<std::string, int, float>> settings;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_INTEGRATORS_INTEGRATORSETTINGS_H_
