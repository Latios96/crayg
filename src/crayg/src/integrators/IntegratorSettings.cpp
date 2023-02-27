#include "IntegratorSettings.h"
#include "utils/ToStringHelper.h"

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
        switch (entry.second.index()) {
        case 0:
            toStringHelper.addMember(entry.first, fmt::format("{}", std::get<std::string>(entry.second)));
            break;
        case 1:
            toStringHelper.addMember(entry.first, fmt::format("{}", std::get<int>(entry.second)));
            break;
        case 2:
            toStringHelper.addMember(entry.first, fmt::format("{}", std::get<float>(entry.second)));
            break;
        }
    }
    os << toStringHelper.finish();
    return os;
}

} // crayg