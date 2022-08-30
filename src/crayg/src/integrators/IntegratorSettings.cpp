#include "IntegratorSettings.h"

namespace crayg {

IntegratorSettings::IntegratorSettings() = default;
IntegratorSettings::IntegratorSettings(const std::unordered_map<std::string,
                                                                IntegratorSettingsValue> &settings)
    : settings(settings) {}
IntegratorSettingsValue IntegratorSettings::getOrDefault(const std::string &name,
                                                         const IntegratorSettingsValue &defaultValue) const {
    if (settings.find(name) == settings.end()) {
        return defaultValue;
    }
    return settings.at(name);
}

} // crayg