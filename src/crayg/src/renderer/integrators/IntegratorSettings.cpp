#include "IntegratorSettings.h"
#include "crayg/foundation/objects/ToStringHelper.h"

namespace crayg {

IntegratorSettings::IntegratorSettings() = default;

IntegratorSettings::IntegratorSettings(const std::unordered_map<std::string, IntegratorSettingsValue> &settings)
    : settings(settings) {
}

IntegratorSettingsValue IntegratorSettings::getOrDefault(const std::string &name,
                                                         const IntegratorSettingsValue &defaultValue) const {
    if (settings.find(name) == settings.end()) {
        return defaultValue;
    }
    return settings.at(name);
}

bool IntegratorSettings::operator==(const IntegratorSettings &rhs) const {
    return settings == rhs.settings;
}

bool IntegratorSettings::operator!=(const IntegratorSettings &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const IntegratorSettings &settings) {
    ToStringHelper toStringHelper("IntegratorSettings");
    for (const auto &entry : settings.settings) {
        toStringHelper.addMember(entry.first, fmt::format("{}", entry.second));
    }
    os << toStringHelper.finish();
    return os;
}

}